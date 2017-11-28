extern int UseDisallowedGroup;
extern int UseAllowedGroup;
extern int debug_enabled;
extern char Default_NTDomain[DNLEN+1];
extern const char * errormsg;

/* Debugging stuff */
#if defined(__GNUC__)			/* this is really a gcc-ism */
#include <stdio.h>
#include <unistd.h>
static char *__foo;
#define debug(X...) if (debug_enabled) { \
                    fprintf(stderr,"nt_auth[%d](%s:%d): ", getpid(), \
                    ((__foo=strrchr(__FILE__,'/'))==NULL?__FILE__:__foo+1),\
                    __LINE__);\
                    fprintf(stderr,X); }
#else /* __GNUC__ */
static void
debug(char *format,...)
{
    if (debug_enabled) {
        va_list args;

        va_start(args,format);
        fprintf(stderr, "nt_auth[%d]: ",getpid());
        vfprintf(stderr, format, args);
        va_end(args);
    }
}
#endif /* __GNUC__ */

int Valid_User(char *,char *, char *);

#endif
