@@ -76,6 +76,7 @@
 #include "pqsort.h" /* Partial qsort for SORT+LIMIT */
 #include "zipmap.h" /* Compact dictionary-alike data structure */
 #include "sha1.h"   /* SHA1 is used for DEBUG DIGEST */
+#include "release.h" /* Release and/or git repository information */
 
 /* Error codes */
 #define REDIS_OK                0
@@ -7175,6 +7176,8 @@ static sds genRedisInfoString(void) {
     bytesToHuman(hmem,zmalloc_used_memory());
     info = sdscatprintf(sdsempty(),
         "redis_version:%s\r\n"
+        "redis_git_sha1:%s\r\n"
+        "redis_git_dirty:%d\r\n"
         "arch_bits:%s\r\n"
         "multiplexing_api:%s\r\n"
         "process_id:%ld\r\n"
@@ -7199,6 +7202,8 @@ static sds genRedisInfoString(void) {
         "vm_enabled:%d\r\n"
         "role:%s\r\n"
         ,REDIS_VERSION,
+        REDIS_GIT_SHA1,
+        REDIS_GIT_DIRTY > 0,
         (sizeof(long) == 8) ? "64" : "32",
         aeGetApiName(),
         (long) getpid(),