             e = sdscat(e,"\r\n");
             addReplySds(c,e);
         }
     } else if (!strcasecmp(c->argv[1]->ptr,"set")) {
         if (c->argc < 3 || c->argc % 2 == 0) goto numargserr;
         sentinelSetCommand(c);
+    } else if (!strcasecmp(c->argv[1]->ptr,"info-cache")) {
+        /* SENTINEL INFO-CACHE <name> */
+        if (c->argc < 2) goto numargserr;
+        mstime_t now = mstime();
+
+        /* Create an ad-hoc dictionary type so that we can iterate
+         * a dictionary composed of just the master groups the user
+         * requested. */
+        dictType copy_keeper = instancesDictType;
+        copy_keeper.valDestructor = NULL;
+        dict *masters_local = sentinel.masters;
+        if (c->argc > 2) {
+            masters_local = dictCreate(&copy_keeper, NULL);
+
+            for (int i = 2; i < c->argc; i++) {
+                sentinelRedisInstance *ri;
+                ri = sentinelGetMasterByName(c->argv[i]->ptr);
+                if (!ri) continue; /* ignore non-existing names */
+                dictAdd(masters_local, ri->name, ri);
+            }
+        }
+
+        /* Reply format:
+         *   1.) master name
+         *   2.) 1.) info from master
+         *       2.) info from replica
+         *       ...
+         *   3.) other master name
+         *   ...
+         */
+        addReplyMultiBulkLen(c,dictSize(masters_local) * 2);
+
+        dictIterator  *di;
+        dictEntry *de;
+        di = dictGetIterator(masters_local);
+        while ((de = dictNext(di)) != NULL) {
+            sentinelRedisInstance *ri = dictGetVal(de);
+            addReplyBulkCBuffer(c,ri->name,strlen(ri->name));
+            addReplyMultiBulkLen(c,dictSize(ri->slaves) + 1); /* +1 for self */
+            addReplyMultiBulkLen(c,2);
+            addReplyLongLong(c, now - ri->info_refresh);
+            if (ri->info)
+                addReplyBulkCBuffer(c,ri->info,sdslen(ri->info));
+            else
+                addReply(c,shared.nullbulk);
+
+            dictIterator *sdi;
+            dictEntry *sde;
+            sdi = dictGetIterator(ri->slaves);
+            while ((sde = dictNext(sdi)) != NULL) {
+                sentinelRedisInstance *sri = dictGetVal(sde);
+                addReplyMultiBulkLen(c,2);
+                addReplyLongLong(c, now - sri->info_refresh);
+                if (sri->info)
+                    addReplyBulkCBuffer(c,sri->info,sdslen(sri->info));
+                else
+                    addReply(c,shared.nullbulk);
+            }
+            dictReleaseIterator(sdi);
+        }
+        dictReleaseIterator(di);
+        if (masters_local != sentinel.masters) dictRelease(masters_local);
+    } else if (!strcasecmp(c->argv[1]->ptr,"simulate-failure")) {
+        /* SENTINEL SIMULATE-FAILURE <flag> <flag> ... <flag> */
+        int j;
+
+        sentinel.simfailure_flags = SENTINEL_SIMFAILURE_NONE;
+        for (j = 2; j < c->argc; j++) {
+            if (!strcasecmp(c->argv[j]->ptr,"crash-after-election")) {
+                sentinel.simfailure_flags |=
+                    SENTINEL_SIMFAILURE_CRASH_AFTER_ELECTION;
+                serverLog(LL_WARNING,"Failure simulation: this Sentinel "
+                    "will crash after being successfully elected as failover "
+                    "leader");
+            } else if (!strcasecmp(c->argv[j]->ptr,"crash-after-promotion")) {
+                sentinel.simfailure_flags |=
+                    SENTINEL_SIMFAILURE_CRASH_AFTER_PROMOTION;
+                serverLog(LL_WARNING,"Failure simulation: this Sentinel "
+                    "will crash after promoting the selected slave to master");
+            } else if (!strcasecmp(c->argv[j]->ptr,"help")) {
+                addReplyMultiBulkLen(c,2);
+                addReplyBulkCString(c,"crash-after-election");
+                addReplyBulkCString(c,"crash-after-promotion");
+            } else {
+                addReplyError(c,"Unknown failure simulation specified");
+                return;
+            }
+        }
+        addReply(c,shared.ok);
     } else {
         addReplyErrorFormat(c,"Unknown sentinel subcommand '%s'",
                                (char*)c->argv[1]->ptr);
     }
     return;
 
 numargserr:
     addReplyErrorFormat(c,"Wrong number of arguments for 'sentinel %s'",
                           (char*)c->argv[1]->ptr);
 }
 
-/* SENTINEL INFO [section] */
-void sentinelInfoCommand(redisClient *c) {
-    char *section = c->argc == 2 ? c->argv[1]->ptr : "default";
-    sds info = sdsempty();
-    int defsections = !strcasecmp(section,"default");
-    int sections = 0;
+#define info_section_from_redis(section_name) do { \
+    if (defsections || allsections || !strcasecmp(section,section_name)) { \
+        sds redissection; \
+        if (sections++) info = sdscat(info,"\r\n"); \
+        redissection = genRedisInfoString(section_name); \
+        info = sdscatlen(info,redissection,sdslen(redissection)); \
+        sdsfree(redissection); \
+    } \
+} while(0)
 
+/* SENTINEL INFO [section] */
+void sentinelInfoCommand(client *c) {
     if (c->argc > 2) {
         addReply(c,shared.syntaxerr);
         return;
     }
 
-    if (!strcasecmp(section,"server") || defsections) {
-        if (sections++) info = sdscat(info,"\r\n");
-        sds serversection = genRedisInfoString("server");
-        info = sdscatlen(info,serversection,sdslen(serversection));
-        sdsfree(serversection);
+    int defsections = 0, allsections = 0;
+    char *section = c->argc == 2 ? c->argv[1]->ptr : NULL;
+    if (section) {
+        allsections = !strcasecmp(section,"all");
+        defsections = !strcasecmp(section,"default");
+    } else {
+        defsections = 1;
     }
 
-    if (!strcasecmp(section,"sentinel") || defsections) {
+    int sections = 0;
+    sds info = sdsempty();
+
+    info_section_from_redis("server");
+    info_section_from_redis("clients");
+    info_section_from_redis("cpu");
+    info_section_from_redis("stats");
+
+    if (defsections || allsections || !strcasecmp(section,"sentinel")) {
         dictIterator *di;
         dictEntry *de;
         int master_id = 0;
 
         if (sections++) info = sdscat(info,"\r\n");
         info = sdscatprintf(info,
             "# Sentinel\r\n"
             "sentinel_masters:%lu\r\n"
             "sentinel_tilt:%d\r\n"
             "sentinel_running_scripts:%d\r\n"
-            "sentinel_scripts_queue_length:%ld\r\n",
+            "sentinel_scripts_queue_length:%ld\r\n"
+            "sentinel_simulate_failure_flags:%lu\r\n",
             dictSize(sentinel.masters),
             sentinel.tilt,
             sentinel.running_scripts,
-            listLength(sentinel.scripts_queue));
+            listLength(sentinel.scripts_queue),
+            sentinel.simfailure_flags);
 
         di = dictGetIterator(sentinel.masters);
         while((de = dictNext(di)) != NULL) {
             sentinelRedisInstance *ri = dictGetVal(de);
             char *status = "ok";
 
