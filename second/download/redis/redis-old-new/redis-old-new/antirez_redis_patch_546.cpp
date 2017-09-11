@@ -1556,6 +1556,11 @@ void bitcountCommand(redisClient *c);
 void bitposCommand(redisClient *c);
 void replconfCommand(redisClient *c);
 void waitCommand(redisClient *c);
+void geoEncodeCommand(redisClient *c);
+void geoDecodeCommand(redisClient *c);
+void geoRadiusByMemberCommand(redisClient *c);
+void geoRadiusCommand(redisClient *c);
+void geoAddCommand(redisClient *c);
 void pfselftestCommand(redisClient *c);
 void pfaddCommand(redisClient *c);
 void pfcountCommand(redisClient *c);
@@ -1588,4 +1593,8 @@ void redisLogHexDump(int level, char *descr, void *value, size_t len);
 #define redisDebugMark() \
     printf("-- MARK %s:%d --\n", __FILE__, __LINE__)
 
+/***** TEMPORARY *******/
+#include "zset.h"
+/***** END TEMPORARY *******/
+
 #endif