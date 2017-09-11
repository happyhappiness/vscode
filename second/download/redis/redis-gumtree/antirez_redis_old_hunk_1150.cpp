
#include <unistd.h> /* for _exit() */

#define assert(_e) ((_e)?(void)0 : (_redisAssert(#_e,__FILE__,__LINE__),_exit(1)))

void _redisAssert(char *estr, char *file, int line);

#endif
