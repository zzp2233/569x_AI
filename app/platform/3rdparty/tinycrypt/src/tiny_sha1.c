/*
 *  FIPS-180-1 compliant SHA-1 implementation
 *
 *  Based on TropicSSL: Copyright (C) 2017 Shanghai Real-Thread Technology Co., Ltd
 *
 *  Based on XySSL: Copyright (C) 2006-2008  Christophe Devine
 *
 *  Copyright (C) 2009  Paul Bakker <polarssl_maintainer at polarssl dot org>
 *
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above copyright
 *      notice, this list of conditions and the following disclaimer in the
 *      documentation and/or other materials provided with the distribution.
 *    * Neither the names of PolarSSL or XySSL nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 *  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 *  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/*
 *  The SHA-1 standard was published by NIST in 1993.
 *
 *  http://www.itl.nist.gov/fipspubs/fip180-1.htm
 */

#include "tinycrypt_config.h"

#if defined(TINY_CRYPT_SHA1)

#include "tinycrypt.h"

#include <string.h>
// #include <stdio.h>

/*
 * 32-bit integer manipulation macros (big endian)
 */
#ifndef GET_ULONG_BE
#define GET_ULONG_BE(n,b,i)                             \
    {                                                   \
        (n) = ( (uint32_t) (b)[(i)    ] << 24 )    \
            | ( (uint32_t) (b)[(i) + 1] << 16 )    \
            | ( (uint32_t) (b)[(i) + 2] <<  8 )    \
            | ( (uint32_t) (b)[(i) + 3]       );   \
    }
#endif

#ifndef PUT_ULONG_BE
#define PUT_ULONG_BE(n,b,i)                             \
    {                                                   \
        (b)[(i)    ] = (uint8_t) ( (n) >> 24 );   \
        (b)[(i) + 1] = (uint8_t) ( (n) >> 16 );   \
        (b)[(i) + 2] = (uint8_t) ( (n) >>  8 );   \
        (b)[(i) + 3] = (uint8_t) ( (n)       );   \
    }
#endif

/*
 * SHA-1 context setup
 */
void tiny_sha1_starts(tiny_sha1_context * ctx)
{
    ctx->total[0] = 0;
    ctx->total[1] = 0;

    ctx->state[0] = 0x67452301;
    ctx->state[1] = 0xEFCDAB89;
    ctx->state[2] = 0x98BADCFE;
    ctx->state[3] = 0x10325476;
    ctx->state[4] = 0xC3D2E1F0;
}

static void sha1_process(tiny_sha1_context * ctx, uint8_t data[64])
{
    uint32_t temp, W[16], A, B, C, D, E;

    GET_ULONG_BE(W[0], data, 0);
    GET_ULONG_BE(W[1], data, 4);
    GET_ULONG_BE(W[2], data, 8);
    GET_ULONG_BE(W[3], data, 12);
    GET_ULONG_BE(W[4], data, 16);
    GET_ULONG_BE(W[5], data, 20);
    GET_ULONG_BE(W[6], data, 24);
    GET_ULONG_BE(W[7], data, 28);
    GET_ULONG_BE(W[8], data, 32);
    GET_ULONG_BE(W[9], data, 36);
    GET_ULONG_BE(W[10], data, 40);
    GET_ULONG_BE(W[11], data, 44);
    GET_ULONG_BE(W[12], data, 48);
    GET_ULONG_BE(W[13], data, 52);
    GET_ULONG_BE(W[14], data, 56);
    GET_ULONG_BE(W[15], data, 60);

#define S(x,n) ((x << n) | ((x & 0xFFFFFFFF) >> (32 - n)))

#define R(t)                                            \
    (                                                   \
        temp = W[(t -  3) & 0x0F] ^ W[(t - 8) & 0x0F] ^ \
        W[(t - 14) & 0x0F] ^ W[ t      & 0x0F],         \
        ( W[t & 0x0F] = S(temp,1) )                     \
        )

#define P(a,b,c,d,e,x)                                  \
    {                                                   \
        e += S(a,5) + F(b,c,d) + K + x; b = S(b,30);    \
    }

    A = ctx->state[0];
    B = ctx->state[1];
    C = ctx->state[2];
    D = ctx->state[3];
    E = ctx->state[4];

#define F(x,y,z) (z ^ (x & (y ^ z)))
#define K 0x5A827999

    P(A, B, C, D, E, W[0]);
    P(E, A, B, C, D, W[1]);
    P(D, E, A, B, C, W[2]);
    P(C, D, E, A, B, W[3]);
    P(B, C, D, E, A, W[4]);
    P(A, B, C, D, E, W[5]);
    P(E, A, B, C, D, W[6]);
    P(D, E, A, B, C, W[7]);
    P(C, D, E, A, B, W[8]);
    P(B, C, D, E, A, W[9]);
    P(A, B, C, D, E, W[10]);
    P(E, A, B, C, D, W[11]);
    P(D, E, A, B, C, W[12]);
    P(C, D, E, A, B, W[13]);
    P(B, C, D, E, A, W[14]);
    P(A, B, C, D, E, W[15]);
    P(E, A, B, C, D, R(16));
    P(D, E, A, B, C, R(17));
    P(C, D, E, A, B, R(18));
    P(B, C, D, E, A, R(19));

#undef K
#undef F

#define F(x,y,z) (x ^ y ^ z)
#define K 0x6ED9EBA1

    P(A, B, C, D, E, R(20));
    P(E, A, B, C, D, R(21));
    P(D, E, A, B, C, R(22));
    P(C, D, E, A, B, R(23));
    P(B, C, D, E, A, R(24));
    P(A, B, C, D, E, R(25));
    P(E, A, B, C, D, R(26));
    P(D, E, A, B, C, R(27));
    P(C, D, E, A, B, R(28));
    P(B, C, D, E, A, R(29));
    P(A, B, C, D, E, R(30));
    P(E, A, B, C, D, R(31));
    P(D, E, A, B, C, R(32));
    P(C, D, E, A, B, R(33));
    P(B, C, D, E, A, R(34));
    P(A, B, C, D, E, R(35));
    P(E, A, B, C, D, R(36));
    P(D, E, A, B, C, R(37));
    P(C, D, E, A, B, R(38));
    P(B, C, D, E, A, R(39));

#undef K
#undef F

#define F(x,y,z) ((x & y) | (z & (x | y)))
#define K 0x8F1BBCDC

    P(A, B, C, D, E, R(40));
    P(E, A, B, C, D, R(41));
    P(D, E, A, B, C, R(42));
    P(C, D, E, A, B, R(43));
    P(B, C, D, E, A, R(44));
    P(A, B, C, D, E, R(45));
    P(E, A, B, C, D, R(46));
    P(D, E, A, B, C, R(47));
    P(C, D, E, A, B, R(48));
    P(B, C, D, E, A, R(49));
    P(A, B, C, D, E, R(50));
    P(E, A, B, C, D, R(51));
    P(D, E, A, B, C, R(52));
    P(C, D, E, A, B, R(53));
    P(B, C, D, E, A, R(54));
    P(A, B, C, D, E, R(55));
    P(E, A, B, C, D, R(56));
    P(D, E, A, B, C, R(57));
    P(C, D, E, A, B, R(58));
    P(B, C, D, E, A, R(59));

#undef K
#undef F

#define F(x,y,z) (x ^ y ^ z)
#define K 0xCA62C1D6

    P(A, B, C, D, E, R(60));
    P(E, A, B, C, D, R(61));
    P(D, E, A, B, C, R(62));
    P(C, D, E, A, B, R(63));
    P(B, C, D, E, A, R(64));
    P(A, B, C, D, E, R(65));
    P(E, A, B, C, D, R(66));
    P(D, E, A, B, C, R(67));
    P(C, D, E, A, B, R(68));
    P(B, C, D, E, A, R(69));
    P(A, B, C, D, E, R(70));
    P(E, A, B, C, D, R(71));
    P(D, E, A, B, C, R(72));
    P(C, D, E, A, B, R(73));
    P(B, C, D, E, A, R(74));
    P(A, B, C, D, E, R(75));
    P(E, A, B, C, D, R(76));
    P(D, E, A, B, C, R(77));
    P(C, D, E, A, B, R(78));
    P(B, C, D, E, A, R(79));

#undef K
#undef F

    ctx->state[0] += A;
    ctx->state[1] += B;
    ctx->state[2] += C;
    ctx->state[3] += D;
    ctx->state[4] += E;
}

/*
 * SHA-1 process buffer
 */
void tiny_sha1_update(tiny_sha1_context * ctx, uint8_t *input, int ilen)
{
    int fill;
    uint32_t left;

    if (ilen <= 0)
        return;

    left = ctx->total[0] & 0x3F;
    fill = 64 - left;

    ctx->total[0] += ilen;
    ctx->total[0] &= 0xFFFFFFFF;

    if (ctx->total[0] < (uint32_t)ilen)
        ctx->total[1]++;

    if (left && ilen >= fill)
    {
        memcpy((void *)(ctx->buffer + left), (void *)input, fill);
        sha1_process(ctx, ctx->buffer);
        input += fill;
        ilen -= fill;
        left = 0;
    }

    while (ilen >= 64)
    {
        sha1_process(ctx, input);
        input += 64;
        ilen -= 64;
    }

    if (ilen > 0)
    {
        memcpy((void *)(ctx->buffer + left), (void *)input, ilen);
    }
}

static const uint8_t sha1_padding[64] =
{
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/*
 * SHA-1 final digest
 */
void tiny_sha1_finish(tiny_sha1_context * ctx, uint8_t output[20])
{
    uint32_t last, padn;
    uint32_t high, low;
    uint8_t msglen[8];

    high = (ctx->total[0] >> 29)
           | (ctx->total[1] << 3);
    low = (ctx->total[0] << 3);

    PUT_ULONG_BE(high, msglen, 0);
    PUT_ULONG_BE(low, msglen, 4);

    last = ctx->total[0] & 0x3F;
    padn = (last < 56) ? (56 - last) : (120 - last);

    tiny_sha1_update(ctx, (uint8_t *)sha1_padding, padn);
    tiny_sha1_update(ctx, msglen, 8);

    PUT_ULONG_BE(ctx->state[0], output, 0);
    PUT_ULONG_BE(ctx->state[1], output, 4);
    PUT_ULONG_BE(ctx->state[2], output, 8);
    PUT_ULONG_BE(ctx->state[3], output, 12);
    PUT_ULONG_BE(ctx->state[4], output, 16);
}

/*
 * output = SHA-1( input buffer )
 */
void tiny_sha1(uint8_t *input, int ilen, uint8_t output[20])
{
    tiny_sha1_context ctx;

    tiny_sha1_starts(&ctx);
    tiny_sha1_update(&ctx, input, ilen);
    tiny_sha1_finish(&ctx, output);

    memset(&ctx, 0, sizeof(tiny_sha1_context));
}

/*
 * SHA-1 HMAC context setup
 */
void tiny_sha1_hmac_starts(tiny_sha1_context * ctx, uint8_t *key, int keylen)
{
    int i;
    uint8_t sum[20];

    if (keylen > 64)
    {
        tiny_sha1(key, keylen, sum);
        keylen = 20;
        key = sum;
    }

    memset(ctx->ipad, 0x36, 64);
    memset(ctx->opad, 0x5C, 64);

    for (i = 0; i < keylen; i++)
    {
        ctx->ipad[i] = (uint8_t)(ctx->ipad[i] ^ key[i]);
        ctx->opad[i] = (uint8_t)(ctx->opad[i] ^ key[i]);
    }

    tiny_sha1_starts(ctx);
    tiny_sha1_update(ctx, ctx->ipad, 64);

    memset(sum, 0, sizeof(sum));
}

/*
 * SHA-1 HMAC process buffer
 */
void tiny_sha1_hmac_update(tiny_sha1_context * ctx, uint8_t *input, int ilen)
{
    tiny_sha1_update(ctx, input, ilen);
}

/*
 * SHA-1 HMAC final digest
 */
void tiny_sha1_hmac_finish(tiny_sha1_context * ctx, uint8_t output[20])
{
    uint8_t tmpbuf[20];

    tiny_sha1_finish(ctx, tmpbuf);
    tiny_sha1_starts(ctx);
    tiny_sha1_update(ctx, ctx->opad, 64);
    tiny_sha1_update(ctx, tmpbuf, 20);
    tiny_sha1_finish(ctx, output);

    memset(tmpbuf, 0, sizeof(tmpbuf));
}

/*
 * output = HMAC-SHA-1( hmac key, input buffer )
 */
void tiny_sha1_hmac(uint8_t *key, int keylen,
                    uint8_t *input, int ilen, uint8_t output[20])
{
    tiny_sha1_context ctx;

    tiny_sha1_hmac_starts(&ctx, key, keylen);
    tiny_sha1_hmac_update(&ctx, input, ilen);
    tiny_sha1_hmac_finish(&ctx, output);

    memset(&ctx, 0, sizeof(tiny_sha1_context));
}

#endif
