 
 #ifndef __REDIS_ASSERT_H__
 #define __REDIS_ASSERT_H__
 
 #include <unistd.h> /* for _exit() */
 
-#define assert(_e) ((_e)?(void)0 : (_redisAssert(#_e,__FILE__,__LINE__),_exit(1)))
+#define assert(_e) ((_e)?(void)0 : (_serverAssert(#_e,__FILE__,__LINE__),_exit(1)))
 
-void _redisAssert(char *estr, char *file, int line);
+void _serverAssert(char *estr, char *file, int line);
 
 #endif
