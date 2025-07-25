/*
 *  LibNoPoll: A websocket library
 *  Copyright (C) 2024 Advanced Software Production Line, S.L.
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public License
 *  as published by the Free Software Foundation; either version 2.1
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this program; if not, write to the Free
 *  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 *  02111-1307 USA
 *
 *  You may find a copy of the license under this software is released
 *  at COPYING file. This is LGPL software: you are welcome to develop
 *  proprietary applications using this library without any royalty or
 *  fee but returning back any change, improvement or addition in the
 *  form of source code, project image, documentation patches, etc.
 *
 *  For commercial support on build Websocket enabled solutions
 *  contact us:
 *
 *      Postal address:
 *         Advanced Software Production Line, S.L.
 *         Av. Juan Carlos I, Nº13, 2ºC
 *         Alcalá de Henares 28806 Madrid
 *         Spain
 *
 *      Email address:
 *         info@aspl.es - http://www.aspl.es/nopoll
 */
#ifndef __NOPOLL_DECL_H__
#define __NOPOLL_DECL_H__

/**
 * \defgroup nopoll_decl_module Nopoll Declarations: Common Nopoll declarations, Types, macros, and support functions.
 */

/**
 * \addtogroup nopoll_decl_module
 * @{
 */

/**
 * @brief Set a default I/O wait limit from the default, which is 64
 * sockets to 4096. Note that this affects \ref nopoll_loop_wait (when
 * using select() API). If you change this value, you'll have to
 * recompile noPoll so internal structures will be updated. See the
 * following document:
 *
 *   - https://tangentsoft.net/wskfaq/advanced.html
 *   (What are the "64 sockets" limitations?)
 *
 * For Windows platforms, there are two 64-socket limitations:
 *
 * The Windows event mechanism (e.g. WaitForMultipleObjects()) can
 * only wait on 64 event objects at a time. Winsock 2 provides the
 * WSAEventSelect() function which lets you use Windows’ event
 * mechanism to wait for events on sockets. Because it uses Windows’
 * event mechanism, you can only wait for events on 64 sockets at a
 * time. If you want to wait on more than 64 Winsock event objects at
 * a time, you need to use multiple threads, each waiting on no more
 * than 64 of the sockets.
 *
 * The select() function is also limited in certain situations to
 * waiting on 64 sockets at a time. The FD_SETSIZE constant defined in
 * the Winsock header determines the size of the fd_set structures you
 * pass to select(). The default value is 64, but if you define this
 * constant to a different value before including the Winsock header,
 * it accepts that value instead:
 *
 * \code
 *   // define in your code new limit
 *   #define FD_SETSIZE 8192
 *   // then include nopoll.h  (you need to recompile noPoll)
 *   #include <nopoll.n>
 * \endcode
 *
 * The problem is that modern network stacks are complex, with many
 * parts coming from various sources, including third parties via
 * things like Layered Service Providers. When you change this
 * constant, you’re depending on all these components to play by the
 * new rules. They’re supposed to, but not all do. The typical symptom
 * is that they ignore sockets beyond the 64th in larger fd_set
 * structures. You can get around this limitation with threads, just
 * as in the event object case.
 */
#ifndef FD_SETSIZE
#define FD_SETSIZE 4096
#endif

/* include platform specific configuration */
#include <nopoll_config.h>

/* max buffer size to process incoming handshake */
#define NOPOLL_HANDSHAKE_BUFFER_SIZE 1536

/* include this at this place to load GNU extensions */
#if defined(__GNUC__)
#  ifndef _GNU_SOURCE
#  define _GNU_SOURCE
#  endif
#  define __NOPOLL_PRETTY_FUNCTION__ __PRETTY_FUNCTION__
#  define __NOPOLL_LINE__            __LINE__
#  define __NOPOLL_FILE__            __FILE__
#elif defined(_MSC_VER)
#  define __NOPOLL_PRETTY_FUNCTION__ __FUNCDNAME__
#  define __NOPOLL_LINE__            __LINE__
#  define __NOPOLL_FILE__            __FILE__
#else
/* unknown compiler */
#define __NOPOLL_PRETTY_FUNCTION__ ""
#define __NOPOLL_LINE__            0
#define __NOPOLL_FILE__            ""
#endif

// #include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

/* only include unistd.h if unix platform is found or gnu gcc compiler
 * is found */
#if defined(__GNUC__) || defined(NOPOLL_OS_UNIX)
# include <unistd.h>
#endif

// #include <sys/types.h>
// #include <sys/stat.h>
// #include <fcntl.h>
#include <ctype.h>

/* Direct portable mapping definitions */
#if defined(NOPOLL_OS_UNIX)

/* Portable definitions while using noPoll Library */
#define NOPOLL_EINTR           EINTR
/**
 * @brief Portable definition for EWOULDBLOCK errno code.
 */
#define NOPOLL_EWOULDBLOCK     EWOULDBLOCK
#define NOPOLL_EINPROGRESS     EINPROGRESS
#define NOPOLL_ENOTCONN        ENOTCONN
#define NOPOLL_EAGAIN          EAGAIN
#define NOPOLL_SOCKET          int
#define NOPOLL_INVALID_SOCKET  -1
#define NOPOLL_SOCKET_ERROR    -1
#define nopoll_close_socket(s) do {if ( s >= 0) {close (s);}} while (0)
#define nopoll_is_disconnected (errno == EPIPE)

#endif /* end defined(AXL_OS_UNIX) */

#if defined(NOPOLL_OS_RTTHREAD)

// #include <rtthread.h>

/** let's have support for R_OK if it is not defined **/
#  ifndef R_OK
#   define R_OK        4
#  endif

/* Portable definitions while using noPoll Library */
#define NOPOLL_EINTR           EINTR
/**
 * @brief Portable definition for EWOULDBLOCK errno code.
 */
#define NOPOLL_EWOULDBLOCK     EWOULDBLOCK
#define NOPOLL_EINPROGRESS     EINPROGRESS
#define NOPOLL_ENOTCONN        ENOTCONN
#define NOPOLL_EAGAIN          EAGAIN
#define NOPOLL_SOCKET          int
#define NOPOLL_INVALID_SOCKET  -1
#define NOPOLL_SOCKET_ERROR    -1
#define nopoll_close_socket(s) do {if ( s >= 0) {closesocket (s);}} while (0)

#endif /* end defined(AXL_OS_UNIX) */

#if defined(NOPOLL_OS_WIN32)

/** let's have support for R_OK if it is not defined **/
#  ifndef R_OK
#   define R_OK        4
#  endif


/* additional includes for the windows platform */

/* _WIN32_WINNT note: If the application including the header defines
 * the _WIN32_WINNT, it must include the bits defined by the value
 * 0x501. */
#ifndef _WIN32_WINNT
#  define _WIN32_WINNT 0x501
#elif _WIN32_WINNT < 0x501
#  undef _WIN32_WINNT
#  define _WIN32_WINNT 0x501
#endif
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <fcntl.h>
#include <io.h>
#include <process.h>
#include <time.h>

#ifdef _MSC_FULL_VER
#define strcasecmp(string1, string2) _stricmp(string1, string2)
#endif

#define NOPOLL_EINTR           WSAEINTR
#define NOPOLL_EWOULDBLOCK     WSAEWOULDBLOCK
#define NOPOLL_EINPROGRESS     WSAEINPROGRESS
#define NOPOLL_ENOTCONN        WSAENOTCONN
#define NOPOLL_EAGAIN          WSAEWOULDBLOCK
#define SHUT_RDWR              SD_BOTH
#define SHUT_WR                SD_SEND
#define NOPOLL_SOCKET          SOCKET
#define NOPOLL_INVALID_SOCKET  INVALID_SOCKET
#define NOPOLL_SOCKET_ERROR    SOCKET_ERROR
#define nopoll_close_socket(s) do {if ( s >= 0) {closesocket (s);}} while (0)
#define uint16_t               u_short
#define nopoll_is_disconnected ((errno == WSAESHUTDOWN) || (errno == WSAECONNABORTED) || (errno == WSAECONNRESET))

/* a definition to avoid warnings */
#define strlen (int) strlen

/* no link support windows */
#define S_ISLNK(m) (0)

#endif /* end defined(NOPOLL_OS_WINDOWS) */

#if defined(NOPOLL_OS_UNIX)
#include <sys/types.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <time.h>
#include <unistd.h>
#endif

#if defined(NOPOLL_OS_RTTHREAD)
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
// #include <rtthread.h>

// #include <sys/types.h>
// #include <fcntl.h>
#include <lwip/netdb.h>
#include <lwip/sockets.h>
#include <time.h>
// #include <unistd.h>

#ifdef send
#undef send
#endif

#endif


/* additional headers for poll support */
#if defined(NOPOLL_HAVE_POLL)
#include <sys/poll.h>
#endif

/* additional headers for linux epoll support */
#if defined(NOPOLL_HAVE_EPOLL)
#include <sys/epoll.h>
#endif

#include <errno.h>

#if defined(NOPOLL_OS_WIN32)
/* errno redefinition for windows platform. this declaration must
 * follow the previous include. */
#ifdef  errno
#undef  errno
#endif
#define errno (WSAGetLastError())
#endif

#if defined(NOPOLL_OS_RTTHREAD)
#ifdef  errno
#undef  errno
#endif
int *_os_errno(void);
#define errno (*_os_errno())
#endif

/**
 * @brief Common definition to have false (\ref nopoll_false) value (which is defined to 0 integer value).
 */
#define nopoll_false (false)
/**
 * @brief Common definition to have true (\ref nopoll_true) value (which is defined to 1 integer value).
 */
#define nopoll_true  (true)

/**
 * @brief Bool definition for the Nopoll toolkit. This type built on
 * top of <b>int</b> is used along with \ref nopoll_false and \ref
 * nopoll_true to model those API functions and attributes that
 * returns or receive a boolean state.
 */
typedef bool nopoll_bool;

/**
 * @brief Pointer to any structure definition. It should be required
 * to use this definition, however, some platforms doesn't support the
 * <b>void *</b> making it necessary to use the <b>char *</b>
 * definition as a general way to represent references.
 */
typedef void * noPollPtr;

/**
 * @brief Execution context object used by the API to provide default
 * settings.
 */
typedef struct _noPollCtx noPollCtx;

/**
 * @brief Abstraction that represents a connection that maybe be a listener created by \ref nopoll_listener_new or because the connection was received as a consequence of that call, or because it is a client connection created by \ref nopoll_conn_new
 *
 * See noPoll API because there are other methods to create connections (not only previous mentioned functions).
 */
typedef struct _noPollConn noPollConn;

/**
 * @brief Optional connection options to change default behaviour.
 */
typedef struct _noPollConnOpts noPollConnOpts;

/**
 * @brief Abstraction that represents a selected IO wait mechanism.
 */
typedef struct _noPollIoEngine noPollIoEngine;

/**
 * @brief Abstraction that represents a single websocket message
 * received.
 */
typedef struct _noPollMsg noPollMsg;

/**
 * @brief Abstraction that represents the status and data exchanged
 * during the handshake.
 */
typedef struct _noPollHandshake noPollHandShake;

/**
 * @brief Nopoll debug levels.
 *
 * While reporting log to the console, these levels are used to report
 * the severity for such log.
 */
typedef enum
{
    /**
     * @brief Debug level. Only used to report common
     * circumstances that represent the proper functionality.
     */
    NOPOLL_LEVEL_DEBUG,
    /**
     * @brief Warning level. Only used to report that an internal
     * issue have happend that could be interesting while
     * reporting error, but it could also mean common situations.
     */
    NOPOLL_LEVEL_WARNING,
    /**
     * @brief Critical level. Only used to report critical
     * situations where some that have happened shouldn't.
     *
     * This level should only be used while reporting critical
     * situations.
     */
    NOPOLL_LEVEL_CRITICAL
}
noPollDebugLevel;

/**
 * @brief Describes the connection role (how it was initiated).
 */
typedef enum
{
    /**
     * @brief Unknown role, returned/used when the connection isn't defined.
     */
    NOPOLL_ROLE_UNKNOWN,
    /**
     * @brief When the connection was created connecting to a web
     * socket server (see \ref nopoll_conn_new).
     */
    NOPOLL_ROLE_CLIENT,
    /**
     * @brief When the connection was accepted being a listener
     * process.
     */
    NOPOLL_ROLE_LISTENER,
    /**
     * @brief When the connection was created by \ref
     * nopoll_listener_new to accept incoming connections.
     */
    NOPOLL_ROLE_MAIN_LISTENER
} noPollRole;

/**
 * @brief List of supported IO waiting mechanism available.
 */
typedef enum
{
    /**
     * @brief Selects the default (best) IO mechanism found on the
     * system.
     */
    NOPOLL_IO_ENGINE_DEFAULT,
    /**
     * @brief Selects the select(2) based IO wait mechanism.
     */
    NOPOLL_IO_ENGINE_SELECT,
    /**
     * @brief Selects the poll(2) based IO wait mechanism.
     */
    NOPOLL_IO_ENGINE_POLL,
    /**
     * @brief Selects the epoll(2) based IO wait mechanism.
     */
    NOPOLL_IO_ENGINE_EPOLL
} noPollIoEngineType;

/**
 * @brief Support macro to allocate memory using nopoll_calloc function,
 * making a casting and using the sizeof keyword.
 *
 * @param type The type to allocate
 * @param count How many items to allocate.
 *
 * @return A newly allocated pointer.
 */
#define nopoll_new(type, count) (type *) nopoll_calloc (count, sizeof (type))

/**
 * @brief Allows to check a condition and return if it is not meet.
 *
 * @param ctx The context where the operation will take place.
 * @param expr The expresion to check.
 */
#define nopoll_return_if_fail(ctx, expr)                    \
    if (!(expr)) {__nopoll_log (ctx, __function_name__, __file__, __line__, NOPOLL_LEVEL_CRITICAL, "Expresion '%s' have failed at %s (%s:%d)", #expr, __NOPOLL_PRETTY_FUNCTION__, __NOPOLL_FILE__, __NOPOLL_LINE__); return;}

/**
 * @brief Allows to check a condition and return the given value if it
 * is not meet.
 *
 * @param ctx The context where the operation will take place.
 *
 * @param expr The expresion to check.
 *
 * @param val The value to return if the expression is not meet.
 */
#define nopoll_return_val_if_fail(ctx, expr, val)           \
    if (!(expr)) { __nopoll_log (ctx, __function_name__, __file__, __line__, NOPOLL_LEVEL_CRITICAL, "Expresion '%s' have failed, returning: %s at %s (%s:%d)", #expr, #val, __NOPOLL_PRETTY_FUNCTION__, __NOPOLL_FILE__, __NOPOLL_LINE__); return val;}


/**
 * @internal
 *
 * C++ support declarations borrowed from the libtool webpage. Thanks
 * you guys for this information.
 *
 * BEGIN_C_DECLS should be used at the beginning of your declarations,
 * so that C++ compilers don't mangle their names.  Use END_C_DECLS at
 * the end of C declarations.
 */
#undef BEGIN_C_DECLS
#undef END_C_DECLS
#ifdef __cplusplus
# define BEGIN_C_DECLS extern "C" {
# define END_C_DECLS }
#else
# define BEGIN_C_DECLS /* empty */
# define END_C_DECLS /* empty */
#endif


/**
 * @brief Type of frames and opcodes supported by noPoll.
 */
typedef enum
{
    /**
     * @brief Support to model unknown op code.
     */
    NOPOLL_UNKNOWN_OP_CODE = -1,
    /**
     * @brief Denotes a continuation frame.
     */
    NOPOLL_CONTINUATION_FRAME = 0,
    /**
     * @brief Denotes a text frame (utf-8 content) and the first
     * frame of the message.
     */
    NOPOLL_TEXT_FRAME         = 1,
    /**
     * @brief Denotes a binary frame and the first frame of the
     * message.
     */
    NOPOLL_BINARY_FRAME       = 2,
    /**
     * @brief Denotes a close frame request.
     */
    NOPOLL_CLOSE_FRAME        = 8,
    /**
     * @brief Denotes a ping frame (used to ring test the circuit
     * and to keep alive the connection).
     */
    NOPOLL_PING_FRAME         = 9,
    /**
     * @brief Denotes a pong frame (reply to ping request).
     */
    NOPOLL_PONG_FRAME         = 10
} noPollOpCode;

/**
 * @brief SSL/TLS protocol type to use for the client or listener
 * connection.
 */
typedef enum
{
#if defined(NOPOLL_HAVE_SSLv23_ENABLED)
    /**
     * @brief Allows to define SSLv23 as SSL protocol used by the
     * client or server connection. A TLS/SSL connection
     * established with these methods may understand SSLv3, TLSv1,
     * TLSv1.1 and TLSv1.2 protocols (\ref NOPOLL_METHOD_SSLV3, \ref NOPOLL_METHOD_TLSV1, ...)
     */
    NOPOLL_METHOD_SSLV23      = 2,
#endif
#if defined(NOPOLL_HAVE_SSLv3_ENABLED)
    /**
     * @brief Allows to define SSLv3 as SSL protocol used by the
     * client or server connection. A connection/listener
     * established with this method will only understand this
     * method.
     */
    NOPOLL_METHOD_SSLV3       = 3,
#endif
#if defined(NOPOLL_HAVE_TLSv10_ENABLED)
    /**
     * @brief Allows to define TLSv1 as SSL protocol used by the
     * client or server connection. A connection/listener
     * established with this method will only understand this
     * method.
     */
    NOPOLL_METHOD_TLSV1       = 4,
#endif
#if defined(NOPOLL_HAVE_TLSv11_ENABLED)
    /**
     * @brief Allows to define TLSv1.1 as SSL protocol used by the
     * client or server connection. A connection/listener
     * established with this method will only understand this
     * method.
     */
    NOPOLL_METHOD_TLSV1_1     = 5,
#endif
#if defined(NOPOLL_HAVE_TLSv12_ENABLED)
    /**
     * @brief Allows to define TLSv1.2 as SSL protocol used by the
     * client or server connection. A connection/listener
     * established with this method will only understand this
     * method.
     */
    NOPOLL_METHOD_TLSV1_2     = 6,
#endif
#if defined(NOPOLL_HAVE_TLS_FLEXIBLE_ENABLED)
    /**
     * @brief Allows to define TLS flexible negotiation where the
     * highest version available will be negotiated by both
     * ends. If you want a particular TLS version, do not use this
     * method.
     *
     * Security consideration: by using this method you are
     * accepting that the remote peer can downgrade to the lowest
     * version of the protocol. In the case you want to use a
     * particular version do not use this flexible method.
     */
    NOPOLL_METHOD_TLS_FLEXIBLE     = 7
#endif
} noPollSslProtocol ;

/**
 * @brief Transport indication to be used by various internal and
 * public APIs
 */
typedef enum
{
    /**
     * Use IPv4 transport
     */
    NOPOLL_TRANSPORT_IPV4 = 1,
#if NOPLL_IPV6
    /**
     * Use IPv6 transport
     */
    NOPOLL_TRANSPORT_IPV6 = 2
#endif
} noPollTransport;

BEGIN_C_DECLS

noPollPtr  nopoll_calloc  (size_t count, size_t size);

noPollPtr  nopoll_realloc (noPollPtr ref, size_t size);

void       nopoll_free    (noPollPtr ref);

END_C_DECLS

#endif

/* @} */
