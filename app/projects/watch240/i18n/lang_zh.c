#include "include.h"

#if !UTE_MULTIPLE_LANGUAGE_SUPPORT

const char * const i18n_zh[] =
{
    [STR_CLOCK]                         = "\xe6\x97\xb6\xe9\x92\x9f\x00",
    [STR_CLOCK_PREVIEW]                 = "表盘预览",
    [STR_MESSAGE]                       = "消息",
    [STR_PHONE]                         = "电话",
    [STR_SPORTS]                        = "运动",
    [STR_SPORTS_CONFIG]                 = "设置目标",

    //[STR_INDOOR_RUN]                    = "室内跑步",
    [STR_FOOTBALL]                      = "足球",
    //[STR_INDOOR_CYCLING]                = "室内自行车",
    //[STR_OUTDOOR_CYCLING]               = "室外自行车",
    //[STR_RUN]                           = "室外跑步",
    //[STR_SWIM]                          = "游泳",
    //[STR_WALK]                          = "爬山",

    [STR_SPORT_RUN]                     = "跑步",
    [STR_SPORT_RIDE_BIKE]               = "骑行",
    [STR_SPORT_JUMP_ROPE]               = "跳绳",
    [STR_SPORT_SWIMMING]                = "游泳",
    [STR_SPORT_BADMINTON]               = "羽毛球",
    [STR_SPORT_TABLE_TENNIS]            = "乒乓球",
    [STR_SPORT_TENNIS]                  = "网球",
    [STR_SPORT_CLIMBING]                = "爬山",
    [STR_SPORT_WALKING]                 = "徒步",
    [STR_SPORT_BASKETBALL]              = "篮球",
    [STR_SPORT_FOOTBALL]                = "足球",
    [STR_SPORT_BASEBALL]                = "棒球",
    [STR_SPORT_VOLLEYBALL]              = "排球",
    [STR_SPORT_CRICKET]                 = "板球",
    [STR_SPORT_RUGBY]                   = "橄榄球",
    [STR_SPORT_HOCKEY]                  = "曲棍球",
    [STR_SPORT_DANCE]                   = "跳舞",
    [STR_SPORT_SPINNING]                = "动感单车",
    [STR_SPORT_YOGA]                    = "瑜伽",
    [STR_SPORT_SIT_UP]                  = "仰卧起坐",
    [STR_SPORT_TREADMILL]               = "跑步机",
    [STR_SPORT_GYMNASTICS]              = "体操",
    [STR_SPORT_BOATING]                 = "划船",
    [STR_SPORT_JUMPING_JACK]            = "开合跳",
    [STR_SPORT_FREE_TRAINING]           = "自由训练",

//    STR_SPORT_INDOOR_WALK,  //室内走路
//    STR_SPORT_INDOOR_RUN,   //室内跑步
//    STR_SPORT_STRENGTH_TRAINING,    //力量训练
//    STR_SPORT_STEP_TRAINING,    //踏步
//    STR_SPORT_HORSE_RIDING,     //骑马
//    STR_SPORT_ELLIPTICAL_TRAINER,       //椭圆机
//    STR_SPORT_TAI_CHI,      //太极
//    STR_SPORT_SHUTTLECOCK,  //毽球
//    STR_SPORT_BOXING,       //拳击
//    STR_SPORT_OUTDOOR_WALK, //户外健走
//    STR_SPORT_TRAIL_RUNNING,    //越野跑
//    STR_SPORT_SKIING,       //滑雪
//    STR_SPORT_ICE_HOCKEY,   //冰球
//    STR_SPORT_TAEKWONDO,    //跆拳道
//    STR_SPORT_VO2MAX_TEST,  //最大摄氧量测试
//    STR_SPORT_ROWING_MACHING,   //划船机
//    STR_SPORT_AIR_WALKER,       //漫步机
//    STR_SPORT_HIKING,       //徒步
//    STR_SPORT_ATHLETICS,    //田径
//    STR_SPORT_WAIST_TRAINING,   //腰腹训练
//    STR_SPORT_KARATE,       //空手道
//    STR_SPORT_COOLDOWN,     //整理放松
//    STR_SPORT_CROSS_TRAINING,   //交叉训练
//    STR_SPORT_PILATES,      //普拉提
//    STR_SPORT_CROSS_FIT,    //交叉配合
//    STR_SPORT_FUNCTIONAL_TRAINING,      //功能性训练
//    STR_SPORT_PHYSICAL_TRAINING,        //体能训练
//    STR_SPORT_ARCHERY,          //射箭
//    STR_SPORT_FLEXIBILITY,      //柔韧度
//    STR_SPORT_MIXED_CARDIO,     //混合有氧
//    STR_SPORT_LATIN_DANCE,      //拉丁舞
//    STR_SPORT_STREET_DANCE,     //街舞
//    STR_SPORT_KICKBOXING,       //自由搏击
//    STR_SPORT_BARRE,            //芭蕾
//    STR_SPORT_AUSTRALIAN_FOOTBALL,  //澳式足球
//    STR_SPORT_MARTIAL_ARTS,     //武术
//    STR_SPORT_STAIRS,           //爬楼
//    STR_SPORT_HANDBALL,         //手球
//    STR_SPORT_BOWLING,          //保龄球
//    STR_SPORT_RACQUETBALL,      //壁球
//    STR_SPORT_CURLING,          //冰壶
//    STR_SPORT_HUNTING,          //打猎
//    STR_SPORT_SNOWBOARDING,     //单板滑雪
//    STR_SPORT_PLAY,             //休闲运动
//    STR_SPORT_AMERICAN_FOOTBALL,    //美式橄榄球
//    STR_SPORT_HAND_CYCLING,     //手摇车
//    STR_SPORT_FISHING,          //钓鱼
//    STR_SPORT_DISC_SPORTS,      //飞盘
//    STR_SPORT_RUGGER,           //橄榄球
//    STR_SPORT_GOLF,             //高尔夫
//    STR_SPORT_FOLK_DANCE,       //民族舞
//    STR_SPORT_DOWNHILL_SKIING,      //高山滑雪
//    STR_SPORT_SNOW_SPORTS,      //雪上运动
//    STR_SPORT_MIND_BODY,        //舒缓冥想类运动
//    STR_SPORT_CORE_TRAINING,    //核心训练
//    STR_SPORT_SKATING,          //滑冰
//    STR_SPORT_FITNESS_GAMING,   //健身游戏
//    STR_SPORT_AEROBICS,         //健身操
//    STR_SPORT_GROUP_TRAINING,   //团体操
//    STR_SPORT_KENDO,            //搏击操
//    STR_SPORT_LACROSSE,         //长曲棍球
//    STR_SPORT_ROLLING,          //泡沫轴筋膜放松
//    STR_SPORT_WRESTLING,        //摔跤
//    STR_SPORT_FENCING,          //击剑
//    STR_SPORT_SOFTBALL,         //垒球
//    STR_SPORT_SINGLE_BAR,       //单杠
//    STR_SPORT_PARALLEL_BARS,    //双杠
//    STR_SPORT_ROLLER_SKATING,   //轮滑
//    STR_SPORT_HULA_HOOP,        //呼啦圈
//    STR_SPORT_DARTS,            //飞镖
//    STR_SPORT_PICKLEBALL,       //匹克球
//    STR_SPORT_HIIT,             //HIIT
//    STR_SPORT_SHOOTING,         //射击
//    STR_SPORT_JUDO,             //柔道
//    STR_SPORT_TRAMPOLINE,       //蹦床
//    STR_SPORT_SKATEBOARDING,    //滑板
//    STR_SPORT_HOVERBOARD,       //平衡车
//    STR_SPORT_BLADING,          //溜旱冰
//    STR_SPORT_PARKOUR,          //跑酷
//    STR_SPORT_DIVING,           //跳水
//    STR_SPORT_SURFING,          //冲浪
//    STR_SPORT_SNORKELING,       //浮潜
//    STR_SPORT_PULL_UP,          //引体向上
//    STR_SPORT_PUSH_UP,          //俯卧撑
//    STR_SPORT_PLANKING,         //平板支撑
//    STR_SPORT_ROCK_CLIMBING,    //攀岩
//    STR_SPORT_HIGHTJUMP,        //跳高
//    STR_SPORT_BUNGEE_JUMPING,   //蹦极
//    STR_SPORT_LONGJUMP,         //跳远
//    STR_SPORT_MARATHON,         //马拉松
//    STR_SPORT_OTHER,            //其他，判断此类型，跳转到其他界面
//    STR_SPORT_CYWEE_SWIM_GNSS,  //第三方游泳算法，带gps数据 20201009
//    STR_SPORT_CYWEE_SWIM,       //第三方游泳算法 20201009
    [STR_SPORT_EXIT_MSG1]               = "运动结束",
    [STR_SPORT_EXIT_MSG2]               = "本次运动量少数据将不会被保存是否结束",
    [STR_SPORT_EXIT_MSG3]               = "本次运动将不会被保存是否结束",

    [STR_STEP]                          = "计步",
    [STR_SLEEP]                         = "睡眠",
    [STR_MUSIC]                         = "音乐",
    [STR_HEART_RATE]                    = "心率",
    [STR_BLOOD_PRESSURE]                = "血压",
    [STR_BLOOD_OXYGEN]                  = "血氧",
    [STR_BLOOD_SUGAR]                   = "血糖",
    [STR_PRESSURE]                      = "压力",
    [STR_WEATHER]                       = "天气",
    [STR_BREATHE]                       = "呼吸",
    [STR_BREATHE_INHALE]                = "吸气",
    [STR_BREATHE_EXHALE]                = "呼气",
    [STR_EVREY_DAY_ACTIVITY]               = "活动记录",
    [STR_CONNECT_PHONE]                 = "连接手机",
    [STR_CALCULATOR]                    = "计算器",
    [STR_ALARM_CLOCK]                   = "闹钟",
    [STR_ALARM_CLOCK_EDIT]              = "编辑闹钟",
    [STR_ALARM_CLOCK_REPEAT]            = "重复",
    [STR_ALARM_CLOCK_SET]               = "闹钟设置",
    [STR_ALARM_CLOCK_MON]               = "星期一",
    [STR_ALARM_CLOCK_TUE]               = "星期二",
    [STR_ALARM_CLOCK_WED]               = "星期三",
    [STR_ALARM_CLOCK_THU]               = "星期四",
    [STR_ALARM_CLOCK_FRI]               = "星期五",
    [STR_ALARM_CLOCK_SAT]               = "星期六",
    [STR_ALARM_CLOCK_SUN]               = "星期日",
    [STR_ALARM_CLOCK1]                  = "闹钟一",
    [STR_ALARM_CLOCK2]                  = "闹钟二",
    [STR_ALARM_CLOCK3]                  = "闹钟三",
    [STR_TIMER]                         = "计时器",
    [STR_STOP_WATCH]                    = "秒表",
    [STR_STOP_WATCH_RECORD]             = "秒表记录",
    [STR_CAMERA]                        = "相机",
    [STR_VOICE_ASSISTANT]               = "语音助手",
    [STR_FIND_PHONE]                    = "查找手机",
    [STR_FIND_PHONEING]                 = "查找中,手机正在响铃",
    [STR_GAME]                          = "游戏",
    [STR_SETTING]                       = "设置",
    [STR_SETTING_LIGHT]                 = "亮度调节",
    [STR_SETTING_DOUSING]               = "熄屏时长",
    [STR_FIVE_SEC]                      = "5秒",
    [STR_TEN_SEC]                       = "10秒",
    [STR_TWENTY_SEC]                    = "20秒",
    [STR_THIRTY_SEC]                    = "30秒",
    [STR_ONE_MIN]                       = "1分钟",
    [STR_FIVE_MIN]                      = "5分钟",
    [STR_NEVER]                         = "永不熄屏",
    [STR_SETTING_UP]                    = "抬腕亮屏",
    [STR_SETTING_DISTURD]               = "勿扰模式",
    [STR_DISTURD_ALL]                   = "全天勿扰",
    [STR_DISTURD_TIM]                   = "定时勿扰",
    [STR_DISTURD_TIM_CTT]               = "开启后,来电和通知静音且不震动(闹钟除外)抬腕不亮屏。是否开启？",
    [STR_DISTURD_TIM_START]             = "开始时间",
    [STR_DISTURD_TIM_END]               = "结束时间",
    [STR_SETTING_SAV]                   = "声音振动",
    [STR_VOL]                           = "声音",
    [STR_SHK]                           = "振动",
    [STR_MEDIA_VOL]                     = "媒体音量",
    [STR_CALL_VOL]                      = "通话音量",
    [STR_SETTING_LANGUAGE]              = "语言切换",
    [STR_LANGUAGE_CN]                   = "中文",
    [STR_LANGUAGE_ENG]                  = "英语",
    [STR_LANGUAGE_FN]                   = "法语",
    [STR_LANGUAGE_RU]                   = "俄语",
    [STR_LANGUAGE_AT]                   = "阿根廷语",
    [STR_LANGUAGE_JP]                   = "日本文",
    [STR_BEATHER_DURATION]                  = "时间设置",
    [STR_CUSTOM_CALENDAR]               = "日期",
    [STR_CUSTOM_TIME]                   = "时间",
    [STR_CUSTOM_DATA]                   = "时间制",
    [STR_SETTING_CALENDAR]              = "日历",
    [STR_SETTING_PASSWORD]              = "密码锁",
    [STR_SETTING_ABOUT]                 = "关于",
    [STR_SETTING_RESTART]               = "重启",
    [STR_SETTING_RSTFY]                 = "恢复出厂",
    [STR_SETTING_OFF]                   = "关机",
    [STR_SETTING_4G]                    = "4G",
    [STR_CALL_RECENT]                   = "最近通话",
    [STR_CALL_RECENT_ONE]               = "13574148110 11/2",
    [STR_CALL_RECENT_TWS]               = "17901231355 7/17",
    [STR_CALL_RECENT_THR]               = "13990522131 12/1",
    [STR_CALL_RECENT_FOUR]              = "18743223323 4/16",
    [STR_CALL_RECENT_FIVE]              = "12134567772 2/28",
    [STR_CALL_RECENT_SIX]               = "19041212131 8/19",
    [STR_CALL_RECENT_SEV]               = "14413135465 1/21",
    [STR_CALL_LINK]                     = "联系人",
    [STR_CALL_LINK_ONE]                 = "张三: 17901231355",
    [STR_CALL_LINK_TWS]                 = "李四: 13990522131",
    [STR_CALL_LINK_THR]                 = "王五: 18743223323",
    [STR_CALL_LINK_FOUR]                = "老六: 12134567772",
    [STR_CALL_LINK_FIVE]                = "麻子: 19041212131",
    [STR_CALL_LINK_SIX]                 = "老九: 13574148110",
    [STR_CALL_LINK_SEV]                 = "客服: 14413135465",
    [STR_CALL_DIAL]                     = "拨号按键",

    [STR_ALIPAY]                        = "支付宝",
    [STR_ALIPAY_BIND_TIP]               = "使用支付宝扫码绑定",
    [STR_ALIPAY_UNBIND_TIP]             = "解绑后将无法使用支付宝各功能，确认解绑？",
    [STR_ALIPAY_UNBIND_TIP2]            = "设备侧已解绑，请在手机支付宝上解绑该设备，完成解绑",
    [STR_CONFIMR]                       = "确认",
    [STR_CANCEL]                        = "取消",
    [STR_BINDING]                       = "正在绑定",
    [STR_BIND_FAILED]                   = "绑定失败",
    [STR_BIND_SUCCESS]                  = "绑定成功",
    [STR_PAYCODE]                       = "付款码",
    [STR_HELP]                          = "帮助",
    [STR_HELP_TILE]                     = "使用支付宝扫码求助",
    [STR_SWITCH_QRCODE]                 = "切换二维码",
    [STR_SWITCH_BARCODE]                = "切换条形码",
    [STR_UNBIND]                        = "解除绑定",

    [STR_ALTITUDE]                      = "海拔",
    [STR_COMPASS]                       = "指南针",
    [STR_FLASHLIGHT]                    = "手电筒",
    [STR_MAP]                           = "地图",
    [STR_SCAN]                          = "扫一扫",
    [STR_STYLE]                         = "菜单风格",
    [STR_VOICE]                         = "语音助手",
    [STR_VOLUME]                        = "调节音量",
    [STR_CALENDAR]                      = "日历",
    [STR_LATEST_APP]                    = "最近应用",
    [STR_CALORIE]                       = "卡路里",
    [STR_STEPS]                         = "步数",
    [STR_DISTANCE]                      = "距离",
    [STR_BAROMETER]                     = "气压计",
    [STR_RECORDER]                      = "录音机",
    [STR_TEMPERATURE]                   = "温度",
    [STR_CELSIUS]                       = "℃",
    [STR_FAHRENHEIT]                    = "℉",
    [STR_YEAR]                          = "年",
    [STR_MON]                           = "月",
    [STR_MDAY]                          = "日",

    [STR_SUNDAY]                        = "周日",
    [STR_MONDAY]                        = "周一",
    [STR_TUESDAY]                       = "周二",
    [STR_WEDNESDAY]                     = "周三",
    [STR_THURSDAY]                      = "周四",
    [STR_FRIDAY]                        = "周五",
    [STR_SATURDAY]                      = "周六",
    [STR_CLOUDY]                        = "多云",
    [STR_SUNNY]                         = "晴",
    [STR_SNOWY]                         = "雪",
    [STR_RAINY]                         = "雨",
    [STR_OVERCAST]                      = "阴",
    [STR_SAND_AND_DUST]                 = "沙尘",
    [STR_WINDY]                         = "大风",
    [STR_HAZE]                          = "雾霾",
    [STR_KCAL]                          = "千卡",
    [STR_KM]                            = "千米",
    [STR_MILE]                          = "英里",
    [STR_HOUR]                          = "时",
    [STR_MIN]                           = "分",
    [STR_SEC]                           = "秒",
    [STR_START]                         = "开始",
    [STR_MEASURING]                     = "测量中",
    [STR_WEAR_CHECK]                    = "佩戴检测中",
    [STR_UNKNOWN]                       = "未知",
    [STR_COMPO_SELECT]                  = "组件选择",

    [STR_STYLE_SUDOKU_1]                = "九宫格",
    [STR_STYLE_SUDOKU_2]                = "九宫格(横向)",
    [STR_STYLE_SUDOKU_3]                = "九宫格(缩放)",
    [STR_STYLE_DISK]                    = "圆盘",
    [STR_STYLE_GRID_1]                  = "网格",
    [STR_STYLE_GRID_2]                  = "网格(缩放)",
    [STR_STYLE_HEXAGON]                 = "六边形",
    [STR_STYLE_HONEYCOMB]               = "蜂窝",
    [STR_STYLE_KALEIDOSCOPE]            = "万花筒",
    [STR_STYLE_LIST_1]                  = "列表",
    [STR_STYLE_LIST_2]                  = "四宫格",
    [STR_STYLE_RING]                    = "环形",
    [STR_STYLE_SKYRER]                  = "天圆地方",
    [STR_STYLE_WATERFALL]               = "瀑布",
    [STR_STYLE_FOOTBALL]                = "足球",
    [STR_STYLE_GRID_HONEYCOMB]          = "网格蜂窝",


    [STR_DEV_NEME]                      = "设备名称",
    [STR_BLE_MAC]                       = "蓝牙地址",
    [STR_SYS_VERSION]                   = "系统版本",
    [STR_NULL]                          = " ",

    [STR_SOOTHING]                      = "舒缓",
    [STR_SLOW]                          = "缓慢",
    [STR_FASTER]                        = "稍快",

    [STR_OK]                            = "确定",
    [STR_MINUTE]                        = "分钟",
    [STR_SETTING_MODE]                  = "模式设置",
    [STR_DRIZZLE]                       ="小雨",
    [STR_MODERATE_RAIN]                 ="阵雨",
    [STR_HEAVY_RAIN]                    ="大雨",
    [STR_SLEET]                         ="雨夹雪",
    [STR_TOMORROW_NIGHT]                ="明夜",
    [STR_CLOUDY_NIGHT]                  ="云遮月",
    [STR_RAINY_NIGHT]                   ="阵雨夜",
    [STR_RAINY_SHOWERS]                 ="雷阵雨",

    [STR_NO_MSG]                        = "没有新消息",

    [STR_FIND_WATCH]                    = "寻找手表",
    [STR_SET_DATA_READ]                 = "当前设定时间如果已与App连接,同步时间将会产生睡眠数据修改.",
    [STR_SET_STEP_COUNT]                = "步数",
    [STR_SET_DISTANCE]                  = "距离",
    [STR_SET_CALORIE]                   = "卡路里",
    [STR_GOAL_ACHIEVE]                  = "目标完成",
    [STR_SEDENTARY_REMIND]              = "久坐提醒",
    [STR_DEEP_SLEEP]                    = "深睡",
    [STR_LIGHT_SLEEP]                   = "浅睡",
    [STR_ALWAKE_SLEEP]                  = "清醒",
    [STR_EYE_MOVE_SLEEP]                = "快速眼动",

};
#endif
