@@ -1594,8 +1594,4 @@ void redisLogHexDump(int level, char *descr, void *value, size_t len);
 #define redisDebugMark() \
     printf("-- MARK %s:%d --\n", __FILE__, __LINE__)
 
-/***** TEMPORARY *******/
-#include "zset.h"
-/***** END TEMPORARY *******/
-
 #endif