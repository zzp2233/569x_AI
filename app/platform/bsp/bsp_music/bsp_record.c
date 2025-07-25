#include "include.h"

#if FUNC_REC_EN
rec_src_t rec_src AT(.buf.record);
rec_cb_t  rec_cb AT(.buf.record);
au_stm_t rec_enc_stm AT(.buf.record);
au_stm_t rec_pcm_stm AT(.buf.record);

u8 rec_obuf[REC_OBUF_SIZE] AT(.rec_buf.obuf);
u8 rec_encbuf[REC_ENC_SIZE] AT(.rec_buf.enc);

u8 frame_cnt = 0;
char fname_buf[100];
void music_enc_control(u8 msg);
bool sbc_encode_init(u8 spr, u8 nch);
void sbc_encode_exit(void);
bool adpcm_encode_init(u8 nch);
bool mpa_encode_init(u32 spr, u32 nchannel, u32 bitrate);
void mpa_encode_exit(void);
void mpa_encode_kick_start(void);



static void mic_rec_start(void)
{

    audio_path_init(AUDIO_PATH_RECORDER);
    audio_path_start(AUDIO_PATH_RECORDER);

}

static void mic_rec_stop(void)
{
    audio_path_exit(AUDIO_PATH_RECORDER);
}

AT(.com_text.record)
bool puts_rec_obuf(u8 *inbuf, u16 len)
{
    rec_cb_t *rec = &rec_cb;
    if (!rec->pcm || !rec->src || rec->sta != REC_RECORDING)
    {
        return false;
    }

    bool puts_ok  = false;
    puts_ok = puts_stm_buf(rec->pcm, inbuf, len);

#if REC_WAV_SUPPORT
    if (rec->src->rec_type == REC_WAV)
    {
        music_enc_control(ENC_MSG_WAV);
    }
#endif
#if REC_ADPCM_SUPPORT
    if (rec->src->rec_type == REC_ADPCM)
    {
        music_enc_control(ENC_MSG_ADPCM);
    }
#endif
#if REC_SBC_SUPPORT
    if (rec->src->rec_type == REC_SBC)
    {
        music_enc_control(ENC_MSG_SBC);
    }
#endif
#if REC_MP3_SUPPORT
    if (rec->src->rec_type == REC_MP3)
    {
        if (rec_cb.pcm->len >= rec_cb.trigger_len)
        {
            mpa_encode_kick_start();
        }
    }
#endif
    return puts_ok;
}

//读取len的ADC数据
AT(.com_text.record)
bool gets_rec_obuf(u8 *buf, u16 len)
{
    if (gets_stm_buf(rec_cb.pcm, buf, len))
    {
        pcm_soft_vol_process((s16 *)buf, rec_cb.dig_gain, len >> 1);    //软件数字GAIN
        return true;
    }
    return false;
}

AT(.com_text.record)
bool puts_rec_encbuf(u8 *buf, u16 len)
{
    return puts_stm_buf(rec_cb.enc, buf, len);
}

AT(.com_text.record)
bool gets_rec_encbuf(u8 *buf, u16 len)
{
    return gets_stm_buf(rec_cb.enc, buf, len);
}

#if REC_WAV_SUPPORT
//wave只需将数据从pcmbuf搬到encbuf
void wave_encode_process(void)
{
    u8 *buf = ab_malloc(512);

    if (!gets_rec_obuf(buf, 512))
    {
        ab_free(buf);
        return;
    }
    puts_rec_encbuf(buf, 512);

    rec_cb_t *rec = &rec_cb;
    if (rec->sta == REC_RECORDING)
    {
        if (!gets_rec_encbuf(buf, 512))
        {
            ab_free(buf);
            return;
        }


        if (!record_file_write(buf, 512, rec->src->rec_type))
        {
            bsp_record_stop();
            ab_free(buf);
            return;
        }

        if (tick_check_expire(rec->tick, REC_SYNC_TIMES))
        {
            rec->tick = tick_get();
            if (!record_file_sync(rec->src->rec_type))
            {
                bsp_record_stop();
            }
        }
    }
    ab_free(buf);
}
#endif

AT(.text.record)
void bsp_record_process(void)
{
    rec_cb_t *rec = &rec_cb;
    if (rec->sta != REC_RECORDING || rec->src->rec_type == REC_WAV)
    {
        return;
    }
    u8 *buf = ab_malloc(512);

    if (rec->sta == REC_RECORDING)
    {
        if (!gets_rec_encbuf(buf, 512))
        {
            ab_free(buf);
            return;
        }
        if (!record_file_write(buf, 512, rec->src->rec_type))
        {
            bsp_record_stop();
            ab_free(buf);
            return;
        }
        if (tick_check_expire(rec->tick, REC_SYNC_TIMES))
        {
            rec->tick = tick_get();
            if (!record_file_sync(rec->src->rec_type))
            {
                bsp_record_stop();
            }
        }
    }
}
AT(.com_text.func.recorder)
void recorder_sdadc_process(u8 *ptr, u32 samples, int ch_mode)
{

#if FUNC_REC_EN

    if (frame_cnt < 4)
    {
        frame_cnt++;
    }
    if (frame_cnt > 3)
    {
        puts_rec_obuf(ptr, (u16)(samples << (1 + ch_mode)));

    }
#endif

//#if MIC_EQ_EN
//    sdadc_pcm_peri_eq(ptr,samples);
//#endif
//    sdadc_pcm_2_dac(ptr, samples, ch_mode);               //推DAC播放
}

AT(.text.func.record)
u8 get_bsp_record_sta(void)
{
    return rec_cb.sta;
}
void bsp_record_stop(void)
{
    rec_cb_t *rec = &rec_cb;
    if (rec->sta == REC_STOP)
    {
        return;
    }
    frame_cnt = 0;


    if (rec->src && rec->src->source_stop != NULL)
    {
        rec->src->source_stop();
    }

    ///写入缓存BUFFER残留的数据
    if (rec->enc->len > 0)
    {
        u32 wlen = rec->enc->len;
        u8 *buf = ab_malloc(512);
        if (gets_rec_encbuf(buf, wlen))
        {
            if (record_file_write(buf, wlen, rec->src->rec_type))
            {
                record_file_sync(rec->src->rec_type);
            }
        }
        ab_free(buf);
    }

    if (rec->flag_file)
    {
        record_file_close(rec->src->rec_type);
    }
#if REC_MP3_SUPPORT
    if (rec->src->rec_type == REC_MP3)
    {
        mpa_encode_exit();
    }
#endif
#if REC_SBC_SUPPORT
    if (rec->src->rec_type == REC_SBC)
    {
        sbc_encode_exit();
    }
#endif
    rec->flag_file = 0;
    rec->flag_dir = 0;
    rec->sta = REC_STOP;
    rec->flag_play = 1;
    if (dev_is_online(DEV_SDCARD))
    {
        sd0_stop(1);
    }

    // 降噪算法初始化，与通话相关
#if FUNC_REC_NR_EN
    dac_fade_out();
    dac_aubuf_clr();
    bt_call_alg_exit();
    dac_set_anl_offset(0);
    bsp_change_volume(sys_cb.vol);
#endif
    bt_sco_pcm_buf_rec_cb_init(NULL);
}

bool bsp_record_start(bool is_sco, u8 type)
{
    rec_cb_t *rec = &rec_cb;
    rec->src = &rec_src;
    rec_src.spr = SPR_16000;
    rec_src.nchannel = 1;
    rec_src.rec_type = type;

    //rec_src.rec_type = REC_WAV;
    rec_src.bitrate = 48000;
    if (!is_sco)
    {
        rec_src.source_start = mic_rec_start;
        rec_src.source_stop  = mic_rec_stop;
    }
    else
    {
        rec_src.source_start = NULL;
        rec_src.source_stop  = NULL;
    }
    frame_cnt = 0;
    rec->sta = REC_STARTING;
    rec->dig_gain = DIG_N0DB;
    if (dev_is_online(DEV_SDCARD))
    {
        sys_cb.cur_dev = DEV_SDCARD;
    }
    else if (dev_is_online(DEV_UDISK))
    {
        sys_cb.cur_dev = DEV_UDISK;
    }
    fsdisk_callback_init(sys_cb.cur_dev);
    if (!rec->flag_file)
    {
        if (!fs_mount())
        {
            return false;
        }
    }
#if MUSIC_REC_FILE_FILTER
    if (rec->first_flag)
    {
        rec->first_flag = 0;
        fs_scan_set(SCAN_SPEED|SCAN_SUB_FOLDER, music_file_filter, music_dir_filter);
        pf_scan_music(0);
    }
#endif

    //创建录音文件夹
    if (!rec->flag_dir)
    {
        if (!record_directory_open((u8 *)fname_buf, sizeof(fname_buf)))
        {
            return false;
        }
        rec->flag_dir = 1;
    }

    //创建录音文件
    if (!rec->flag_file)
    {
        if (!record_file_open((u8 *)fname_buf, sizeof(fname_buf), rec->src->rec_type))
        {
            return false;
        }
        rec->flag_file = 1;
    }

#if REC_WAV_SUPPORT
    if (rec->src->rec_type == REC_WAV)
    {
        if (!record_wav_init(rec->src->nchannel & 0x03, rec->src->spr, rec->src->rec_type))
        {
            return false;
        }
    }
#endif
#if REC_ADPCM_SUPPORT
    if (rec->src->rec_type == REC_ADPCM)
    {
        if (!record_wav_init(rec->src->nchannel & 0x03, rec->src->spr, rec->src->rec_type))
        {
            return false;
        }
        adpcm_encode_init(rec->src->nchannel & 0x03);
    }
#endif
#if REC_MP3_SUPPORT
    if (rec->src->rec_type == REC_MP3)
    {
        rec->trigger_len = 384 << (rec->src->nchannel & 0x03);
        if (!mpa_encode_init(rec->src->spr, rec->src->nchannel, rec->src->bitrate))
        {
            return false;
        }
    }
#endif
#if REC_SBC_SUPPORT
    if (rec->src->rec_type == REC_SBC)
    {
        if (!sbc_encode_init(rec->src->spr, rec->src->nchannel & 0x03))
        {
            return false;
        }
    }
#endif

    memset(&rec_enc_stm, 0, sizeof(rec_enc_stm));                       //output coded data buffer init
    memset(&rec_pcm_stm, 0, sizeof(rec_pcm_stm));                       //input pcm data buffer init
    rec->enc = &rec_enc_stm;
    rec->pcm = &rec_pcm_stm;
    rec->enc->buf = rec->enc->rptr = rec->enc->wptr = rec_encbuf;
    rec->pcm->buf = rec->pcm->rptr = rec->pcm->wptr = rec_obuf;
    rec->enc->size = REC_ENC_SIZE;
    rec->pcm->size = REC_OBUF_SIZE;
    if (rec->src && rec->src->source_start != NULL)
    {
        rec->src->source_start();
    }

    rec->tick = tick_get();
    rec->sta = REC_RECORDING;

    // 降噪算法初始化，与通话相关
#if FUNC_REC_NR_EN
    bt_call_alg_init();
    dac_set_anl_offset(1);
    bsp_change_volume(bsp_bt_get_hfp_vol(sys_cb.hfp_vol));
    dac_fade_in();
    bt_sco_pcm_buf_rec_cb_init(recorder_sdadc_process);
#endif
#if FUNC_REC_SCO
    bt_sco_pcm_buf_rec_cb_init(recorder_sdadc_process);
#endif
    return true;
}

void bsp_record_pause(void)
{
    rec_cb_t *rec = &rec_cb;
    if (rec->sta != REC_RECORDING)
    {
        return;
    }
    printf("record pause\n");
    if (rec->src)
    {
        rec->src->source_stop();
    }
    // if (rec->flag_file) {
    //     record_file_close(rec->src->rec_type);
    // }
#if REC_MP3_SUPPORT
    if (rec->src->rec_type == REC_MP3)
    {
        mpa_encode_exit();
    }
#endif
#if REC_SBC_SUPPORT
    if (rec->src->rec_type == REC_SBC)
    {
        sbc_encode_exit();
    }
#endif
    // rec->flag_file = 0;
    // rec->flag_dir = 0;
    rec->src = 0;
    rec->sta = REC_PAUSE;
    rec->flag_play = 1;
    if (dev_is_online(DEV_SDCARD))
    {
        printf("sd0 stop 1!\n");
        sd0_stop(1);
    }
    // 降噪算法初始化，与通话相关
#if FUNC_REC_NR_EN
    dac_fade_out();
    dac_aubuf_clr();
    bt_call_alg_exit();
    dac_set_anl_offset(0);
    bsp_change_volume(sys_cb.vol);
#endif // FUNC_REC_NR_EN
    bt_sco_pcm_buf_rec_cb_init(NULL);
}

AT(.text.func.record)
void bsp_record_continue(void)
{
    if (rec_cb.sta == REC_PAUSE)
    {
        printf("record continue\n");
        bsp_record_start(false, rec_src.rec_type);
    }
}


void bsp_record_var_init(void)
{
    memset(&rec_cb, 0, sizeof(rec_cb));
    memset(&rec_src, 0, sizeof(rec_src));
    rec_cb.src = &rec_src;
    rec_cb.first_flag = 1;
}
#endif // FUNC_REC_EN
