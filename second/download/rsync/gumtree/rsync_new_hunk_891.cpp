#  endif
# endif
#elif defined(__GNUC__) && defined(__STRICT_ANSI__)
#define alloca __builtin_alloca
#endif

#ifndef HAVE_STRLCPY
size_t strlcpy(char *d, const char *s, size_t bufsize);
#endif

#ifndef HAVE_STRLCAT
size_t strlcat(char *d, const char *s, size_t bufsize);
#endif

#if HAVE_MCHECK_H && defined(__GNUC__)
static inline char *
xstrdup(const char *s)
{
    size_t memsize = strlen(s) + 1;
    char *ptr = malloc(memsize);
    if (!ptr) {
	fprintf(stderr, "virtual memory exhausted.\n");
	exit(EXIT_FAILURE);
    }
    strlcpy(ptr, s, memsize);
    return ptr;
}
#else
#define	xstrdup(_str)	strdup(_str)
#endif  /* HAVE_MCHECK_H && defined(__GNUC__) */

#if HAVE___SECURE_GETENV && !defined(__LCLINT__)
#define	getenv(_s)	__secure_getenv(_s)
#endif

#if !defined HAVE_SNPRINTF || !defined HAVE_C99_VSNPRINTF
#define snprintf rsync_snprintf
int snprintf(char *str,size_t count,const char *fmt,...);
#endif

#define UNUSED(x) x __attribute__((__unused__))

#define PACKAGE "rsync"

#include "popt.h"
