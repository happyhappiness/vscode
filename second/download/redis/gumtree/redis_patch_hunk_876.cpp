         (float)self_ru.ru_stime.tv_sec+(float)self_ru.ru_stime.tv_usec/1000000,
         (float)self_ru.ru_utime.tv_sec+(float)self_ru.ru_utime.tv_usec/1000000,
         (float)c_ru.ru_stime.tv_sec+(float)c_ru.ru_stime.tv_usec/1000000,
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
     if (allsections || defsections || !strcasecmp(section,"cluster")) {
         if (sections++) info = sdscat(info,"\r\n");
         info = sdscatprintf(info,
