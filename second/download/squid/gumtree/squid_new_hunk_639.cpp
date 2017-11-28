extern int UseAllowedGroup;
extern int debug_enabled;
extern char Default_NTDomain[DNLEN+1];
extern const char * errormsg;

/* Debugging stuff */
#if defined(__GNUC__)           /* this is really a gcc-ism */
#include <unistd.h>
static char *__foo;
#define debug(X...) if (debug_enabled) { \
                    fprintf(stderr,"nt_auth[%d](%s:%d): ", getpid(), \
                    ((__foo=strrchr(__FILE__,'/'))==NULL?__FILE__:__foo+1),\
                    __LINE__);\
