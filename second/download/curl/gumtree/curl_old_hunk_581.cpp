void Curl_infof(struct SessionHandle *, const char *fmt, ...);
void Curl_failf(struct SessionHandle *, const char *fmt, ...);

#if defined(CURL_DISABLE_VERBOSE_STRINGS)

#if defined(HAVE_VARIADIC_MACROS_C99)
#define infof(...)  do { } while (0)
#elif defined(HAVE_VARIADIC_MACROS_GCC)
#define infof(x...)  do { } while (0)
#else
#define infof (void)
#endif

#else /* CURL_DISABLE_VERBOSE_STRINGS */

