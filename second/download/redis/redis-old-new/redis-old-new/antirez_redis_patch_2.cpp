@@ -1987,15 +1987,18 @@ void populateCommandTable(void) {
 }
 
 void resetCommandTableStats(void) {
-    int numcommands = sizeof(redisCommandTable)/sizeof(struct redisCommand);
-    int j;
-
-    for (j = 0; j < numcommands; j++) {
-        struct redisCommand *c = redisCommandTable+j;
+    struct redisCommand *c;
+    dictEntry *de;
+    dictIterator *di;
 
+    di = dictGetSafeIterator(server.commands);
+    while((de = dictNext(di)) != NULL) {
+        c = (struct redisCommand *) dictGetVal(de);
         c->microseconds = 0;
         c->calls = 0;
     }
+    dictReleaseIterator(di);
+
 }
 
 /* ========================== Redis OP Array API ============================ */
@@ -2794,7 +2797,7 @@ void bytesToHuman(char *s, unsigned long long n) {
 sds genRedisInfoString(char *section) {
     sds info = sdsempty();
     time_t uptime = server.unixtime-server.stat_starttime;
-    int j, numcommands;
+    int j;
     struct rusage self_ru, c_ru;
     unsigned long lol, bib;
     int allsections = 0, defsections = 0;
@@ -3255,20 +3258,24 @@ sds genRedisInfoString(char *section) {
         (float)c_ru.ru_utime.tv_sec+(float)c_ru.ru_utime.tv_usec/1000000);
     }
 
-    /* cmdtime */
+    /* Command statistics */
     if (allsections || !strcasecmp(section,"commandstats")) {
         if (sections++) info = sdscat(info,"\r\n");
         info = sdscatprintf(info, "# Commandstats\r\n");
-        numcommands = sizeof(redisCommandTable)/sizeof(struct redisCommand);
-        for (j = 0; j < numcommands; j++) {
-            struct redisCommand *c = redisCommandTable+j;
 
+        struct redisCommand *c;
+        dictEntry *de;
+        dictIterator *di;
+        di = dictGetSafeIterator(server.commands);
+        while((de = dictNext(di)) != NULL) {
+            c = (struct redisCommand *) dictGetVal(de);
             if (!c->calls) continue;
             info = sdscatprintf(info,
                 "cmdstat_%s:calls=%lld,usec=%lld,usec_per_call=%.2f\r\n",
                 c->name, c->calls, c->microseconds,
                 (c->calls == 0) ? 0 : ((float)c->microseconds/c->calls));
         }
+        dictReleaseIterator(di);
     }
 
     /* Cluster */