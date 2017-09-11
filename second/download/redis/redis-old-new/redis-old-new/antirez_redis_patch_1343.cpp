@@ -48,6 +48,7 @@
 #include <float.h>
 #include <math.h>
 #include <sys/resource.h>
+#include <sys/utsname.h>
 
 /* Our shared "common" objects */
 
@@ -1739,12 +1740,16 @@ sds genRedisInfoString(char *section) {
 
     /* Server */
     if (allsections || defsections || !strcasecmp(section,"server")) {
+        struct utsname name;
+
         if (sections++) info = sdscat(info,"\r\n");
+        uname(&name);
         info = sdscatprintf(info,
             "# Server\r\n"
             "redis_version:%s\r\n"
             "redis_git_sha1:%s\r\n"
             "redis_git_dirty:%d\r\n"
+            "os:%s %s %s\r\n"
             "arch_bits:%d\r\n"
             "multiplexing_api:%s\r\n"
             "gcc_version:%d.%d.%d\r\n"
@@ -1757,6 +1762,7 @@ sds genRedisInfoString(char *section) {
             REDIS_VERSION,
             redisGitSHA1(),
             strtol(redisGitDirty(),NULL,10) > 0,
+            name.sysname, name.release, name.machine,
             server.arch_bits,
             aeGetApiName(),
 #ifdef __GNUC__