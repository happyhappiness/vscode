
/* Debugging stuff */

SQUIDCEXTERN int debug_enabled;

/* the macro overload style is really a gcc-ism */
#ifdef __GNUC__

#define debug(X...) \
                     if (debug_enabled) { \
                         fprintf(stderr, "%s(%d): pid=%ld :", __FILE__, __LINE__, (long)getpid() ); \
                         fprintf(stderr,X); \
                     } else (void)0

#else /* __GNUC__ */

/* non-GCC compilers can't do the above macro define yet. */
void debug(const char *format,...);
#endif

#endif /* COMPAT_DEBUG_H */
