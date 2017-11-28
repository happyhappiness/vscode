
/******************************************************/
/* Typedefs for missing entries on a system           */
/******************************************************/

/*
 * Ensure that standard type limits are defined for use
 */
#if __cplusplus >= 201103L
#include <cstdint>
#elif HAVE_STDINT_H
#include <stdint.h>
#endif

/* explicit bit sizes */
#if !defined(UINT32_MIN)
#define UINT32_MIN    0x00000000L
#endif
#if !defined(UINT32_MAX)
#define UINT32_MAX    0xFFFFFFFFL
#endif

#if !defined(INT_MAX)
#define INT_MAX    0x7FFFFFFFL // hack but a safe bet (32-bit signed integer)
#endif

#if !defined(INT64_MIN)
/* Native 64 bit system without strtoll() */
#if defined(LONG_MIN) && (SIZEOF_LONG == 8)
#define INT64_MIN    LONG_MIN
#else
/* 32 bit system */
#define INT64_MIN    (-9223372036854775807LL-1LL)
#endif
#endif

#if !defined(INT64_MAX)
/* Native 64 bit system without strtoll() */
#if defined(LONG_MAX) && (SIZEOF_LONG == 8)
#define INT64_MAX    LONG_MAX
#else
/* 32 bit system */
#define INT64_MAX    9223372036854775807LL
#endif
#endif

/*
 * ISO C99 Standard printf() macros for 64 bit integers
 * On some 64 bit platform, HP Tru64 is one, for printf must be used
 * "%lx" instead of "%llx"
 */
#ifndef PRId64
#if _SQUID_WINDOWS_
