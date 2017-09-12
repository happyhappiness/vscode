@@ -51,6 +51,7 @@
 #include <float.h>
 #include <math.h>
 #include <pthread.h>
+#include <sys/resource.h>
 
 /* Our shared "common" objects */
 
@@ -1147,6 +1148,10 @@ sds genRedisInfoString(void) {
     time_t uptime = time(NULL)-server.stat_starttime;
     int j;
     char hmem[64];
+    struct rusage self_ru, c_ru;
+
+    getrusage(RUSAGE_SELF, &self_ru);
+    getrusage(RUSAGE_CHILDREN, &c_ru);
 
     bytesToHuman(hmem,zmalloc_used_memory());
     info = sdscatprintf(sdsempty(),
@@ -1158,6 +1163,10 @@ sds genRedisInfoString(void) {
         "process_id:%ld\r\n"
         "uptime_in_seconds:%ld\r\n"
         "uptime_in_days:%ld\r\n"
+        "used_cpu_sys:%.2f\r\n"
+        "used_cpu_user:%.2f\r\n"
+        "used_cpu_sys_childrens:%.2f\r\n"
+        "used_cpu_user_childrens:%.2f\r\n"
         "connected_clients:%d\r\n"
         "connected_slaves:%d\r\n"
         "blocked_clients:%d\r\n"
@@ -1185,6 +1194,10 @@ sds genRedisInfoString(void) {
         (long) getpid(),
         uptime,
         uptime/(3600*24),
+        (float)self_ru.ru_utime.tv_sec+(float)self_ru.ru_utime.tv_usec/1000000,
+        (float)self_ru.ru_stime.tv_sec+(float)self_ru.ru_stime.tv_usec/1000000,
+        (float)c_ru.ru_utime.tv_sec+(float)c_ru.ru_utime.tv_usec/1000000,
+        (float)c_ru.ru_stime.tv_sec+(float)c_ru.ru_stime.tv_usec/1000000,
         listLength(server.clients)-listLength(server.slaves),
         listLength(server.slaves),
         server.blpop_blocked_clients,