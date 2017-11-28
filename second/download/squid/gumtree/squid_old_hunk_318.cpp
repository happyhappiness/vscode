/*
 * ISO C99 Standard printf() macros for 64 bit integers
 * On some 64 bit platform, HP Tru64 is one, for printf must be used
 * "%lx" instead of "%llx"
 */
#ifndef PRId64
#if _SQUID_MSWIN_		/* Windows native port using MSVCRT */
#define PRId64 "I64d"
#elif SIZEOF_INT64_T > SIZEOF_LONG
#define PRId64 "lld"
#else
#define PRId64 "ld"
#endif
#endif

#ifndef PRIu64
#if _SQUID_MSWIN_		/* Windows native port using MSVCRT */
#define PRIu64 "I64u"
#elif SIZEOF_INT64_T > SIZEOF_LONG
#define PRIu64 "llu"
#else
#define PRIu64 "lu"
#endif
#endif

#ifndef PRIX64
#if _SQUID_MSWIN_		/* Windows native port using MSVCRT */
#define PRIX64 "I64X"
#elif SIZEOF_INT64_T > SIZEOF_LONG
#define PRIX64 "llX"
#else
#define PRIX64 "lX"
#endif
