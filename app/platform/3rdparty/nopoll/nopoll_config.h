/*
 * Nopoll Library nopoll_config.h
 * Platform dependant definitions.
 *
 * This is a generated file.  Please modify 'configure.in'
 */

#ifndef __NOPOLL_CONFIG_H__
#define __NOPOLL_CONFIG_H__

/**
 * \addtogroup nopoll_decl_module
 * @{
 */

/**
 * @brief Allows to convert integer value (including constant values)
 * into a pointer representation.
 *
 * Use the oposite function to restore the value from a pointer to a
 * integer: \ref PTR_TO_INT.
 *
 * @param integer The integer value to cast to pointer.
 *
 * @return A \ref noPollPtr reference.
 */
#ifndef INT_TO_PTR
#define INT_TO_PTR(integer) ((noPollPtr) (integer))
#endif

/**
 * @brief Allows to convert a pointer reference (\ref noPollPtr),
 * which stores an integer that was stored using \ref INT_TO_PTR.
 *
 * Use the oposite function to restore the pointer value stored in the
 * integer value.
 *
 * @param ptr The pointer to cast to a integer value.
 *
 * @return A int value.
 */
#ifndef PTR_TO_INT
#define PTR_TO_INT(ptr) ((int) (ptr))
#endif

/**
 * @brief Allows to get current platform configuration. This is used
 * by Nopoll library but could be used by applications built on top of
 * Nopoll to change its configuration based on the platform information.
 */
// #define NOPOLL_OS_UNIX (1)
#define NOPOLL_OS_RTTHREAD  (1)

/**
 * @internal Allows to now if the platform support vasprintf
 * function. Do not use this macro as it is supposed to be for
 * internal use.
 */
// #define NOPOLL_HAVE_VASPRINTF (0)

/**
 * @brief Indicates that this platform have support for 64bits.
 */
// #define NOPOLL_64BIT_PLATFORM (0)

#define NOPLL_TLS             (0)
#define NOPLL_IPV6            (0)

/**
 * @brief Indicates where we have support for SSL v.3 support.
 */
#define NOPOLL_HAVE_SSLv23_ENABLED (0)

/**
 * @brief Indicates where we have support for SSL v3.0 support. The SSLv3 protocol is deprecated and should not be used.
 */
#define NOPOLL_HAVE_SSLv3_ENABLED (0)

/**
 * @brief Indicates where we have support for TLSv1.0 support.
 */
#define NOPOLL_HAVE_TLSv10_ENABLED (0)

/**
 * @brief Indicates where we have support for TLSv1.1 support.
 */
#define NOPOLL_HAVE_TLSv11_ENABLED (0)

/**
 * @brief Indicates where we have support for TLSv1.2 support.
 */
#define NOPOLL_HAVE_TLSv12_ENABLED (0)


/* @} */

#endif
