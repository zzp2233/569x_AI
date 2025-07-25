/**
 *
 * @file tftp_common.h
 *
 * @author   Logan Gunthorpe <logang@deltatee.com>
 *
 * @brief    Trivial File Transfer Protocol (RFC 1350)
 *
 * Copyright (c) Deltatee Enterprises Ltd. 2013
 * All rights reserved.
 *
 */

/*
 * Redistribution and use in source and binary forms, with or without
 * modification,are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Author: Logan Gunthorpe <logang@deltatee.com>
 *
 */

#ifndef LWIP_HDR_APPS_TFTP_COMMON_H
#define LWIP_HDR_APPS_TFTP_COMMON_H

#include "lwip/apps/tftp_opts.h"
#include "lwip/err.h"
#include "lwip/pbuf.h"
#include "lwip/ip_addr.h"

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup tftp
 * TFTP context containing callback functions for TFTP transfers
 */
struct tftp_context
{
    /**
     * Open file for read/write (server mode only).
     * @param fname Filename
     * @param mode Mode string from TFTP RFC 1350 (netascii, octet, mail)
     * @param write Flag indicating read (0) or write (!= 0) access
     * @returns File handle supplied to other functions
     */
    void* (*open)(const char* fname, const char* mode, u8_t write);
    /**
     * Close file handle
     * @param handle File handle returned by open()/tftp_put()/tftp_get()
     */
    void (*close)(void* handle);
    /**
     * Read from file
     * @param handle File handle returned by open()/tftp_put()/tftp_get()
     * @param buf Target buffer to copy read data to
     * @param bytes Number of bytes to copy to buf
     * @returns &gt;= 0: Success; &lt; 0: Error
     */
    int (*read)(void* handle, void* buf, int bytes);
    /**
     * Write to file
     * @param handle File handle returned by open()/tftp_put()/tftp_get()
     * @param pbuf PBUF adjusted such that payload pointer points
     *             to the beginning of write data. In other words,
     *             TFTP headers are stripped off.
     * @returns &gt;= 0: Success; &lt; 0: Error
     */
    int (*write)(void* handle, struct pbuf* p);
    /**
     * Error indication from client or response from server
     * @param handle File handle set by open()/tftp_get()/tftp_put()
     * @param err error code from client or server
     * @param msg error message from client or server
     * @param size size of msg
     */
    void (*error)(void* handle, int err, const char* msg, int size);
};

#define LWIP_TFTP_MODE_SERVER       0x01
#define LWIP_TFTP_MODE_CLIENT       0x02
#define LWIP_TFTP_MODE_CLIENTSERVER (LWIP_TFTP_MODE_SERVER | LWIP_TFTP_MODE_CLIENT)

err_t tftp_init_common(u8_t mode, const struct tftp_context* ctx);
void tftp_cleanup(void);

#ifdef __cplusplus
}
#endif

#endif /* LWIP_HDR_APPS_TFTP_COMMON_H */
