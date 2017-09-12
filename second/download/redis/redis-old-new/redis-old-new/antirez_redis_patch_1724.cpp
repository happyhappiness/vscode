@@ -1148,9 +1148,11 @@ sds genRedisInfoString(void) {
     int j;
     char hmem[64];
     struct rusage self_ru, c_ru;
+    unsigned long lol, bib;
 
     getrusage(RUSAGE_SELF, &self_ru);
     getrusage(RUSAGE_CHILDREN, &c_ru);
+    getClientsMaxBuffers(&lol,&bib);
 
     bytesToHuman(hmem,zmalloc_used_memory());
     info = sdscatprintf(sdsempty(),
@@ -1169,6 +1171,8 @@ sds genRedisInfoString(void) {
         "used_cpu_user_childrens:%.2f\r\n"
         "connected_clients:%d\r\n"
         "connected_slaves:%d\r\n"
+        "client_longest_output_list:%lu\r\n"
+        "client_biggest_input_buf:%lu\r\n"
         "blocked_clients:%d\r\n"
         "used_memory:%zu\r\n"
         "used_memory_human:%s\r\n"
@@ -1208,6 +1212,7 @@ sds genRedisInfoString(void) {
         (float)c_ru.ru_stime.tv_sec+(float)c_ru.ru_stime.tv_usec/1000000,
         listLength(server.clients)-listLength(server.slaves),
         listLength(server.slaves),
+        lol, bib,
         server.bpop_blocked_clients,
         zmalloc_used_memory(),
         hmem,