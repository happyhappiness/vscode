@@ -60,6 +60,8 @@
 #include "lzf.h"    /* LZF compression library */
 #include "pqsort.h" /* Partial qsort for SORT+LIMIT */
 
+#include "config.h"
+
 /* Error codes */
 #define REDIS_OK                0
 #define REDIS_ERR               -1
@@ -3866,15 +3868,15 @@ static void updateSalvesWaitingBgsave(int bgsaveerr) {
             startbgsave = 1;
             slave->replstate = REDIS_REPL_WAIT_BGSAVE_END;
         } else if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_END) {
-            struct stat buf;
+            struct redis_stat buf;
            
             if (bgsaveerr != REDIS_OK) {
                 freeClient(slave);
                 redisLog(REDIS_WARNING,"SYNC failed. BGSAVE child returned an error");
                 continue;
             }
             if ((slave->repldbfd = open(server.dbfilename,O_RDONLY)) == -1 ||
-                fstat(slave->repldbfd,&buf) == -1) {
+                redis_fstat(slave->repldbfd,&buf) == -1) {
                 freeClient(slave);
                 redisLog(REDIS_WARNING,"SYNC failed. Can't open/stat DB after BGSAVE: %s", strerror(errno));
                 continue;