
/******************************************************/
/* Typedefs for missing entries on a system           */
/******************************************************/

/*
 * ISO C99 Standard printf() macros for 64 bit integers
 * On some 64 bit platform, HP Tru64 is one, for printf must be used
 * "%lx" instead of "%llx"
 */
#ifndef PRId64
#if _SQUID_WINDOWS_
