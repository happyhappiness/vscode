@@ -190,6 +190,7 @@ typedef struct sentinelRedisInstance {
      * are set to NULL no script is executed. */
     char *notification_script;
     char *client_reconfig_script;
+    sds info; /* cached INFO output */
 } sentinelRedisInstance;
 
 /* Main state. */
@@ -983,6 +984,7 @@ sentinelRedisInstance *createSentinelRedisInstance(char *name, int flags, char *
     ri->promoted_slave = NULL;
     ri->notification_script = NULL;
     ri->client_reconfig_script = NULL;
+    ri->info = NULL;
 
     /* Role */
     ri->role_reported = ri->flags & (SRI_MASTER|SRI_SLAVE);
@@ -1015,6 +1017,7 @@ void releaseSentinelRedisInstance(sentinelRedisInstance *ri) {
     sdsfree(ri->slave_master_host);
     sdsfree(ri->leader);
     sdsfree(ri->auth_pass);
+    sdsfree(ri->info);
     releaseSentinelAddr(ri->addr);
 
     /* Clear state into the master if needed. */
@@ -1785,6 +1788,10 @@ void sentinelRefreshInstanceInfo(sentinelRedisInstance *ri, const char *info) {
     int numlines, j;
     int role = 0;
 
+    /* cache full INFO output for instance */
+    sdsfree(ri->info);
+    ri->info = sdsnew(info);
+
     /* The following fields must be reset to a given value in the case they
      * are not found at all in the INFO output. */
     ri->master_link_down_time = 0;
@@ -2777,6 +2784,68 @@ void sentinelCommand(redisClient *c) {
     } else if (!strcasecmp(c->argv[1]->ptr,"set")) {
         if (c->argc < 3 || c->argc % 2 == 0) goto numargserr;
         sentinelSetCommand(c);
+    } else if (!strcasecmp(c->argv[1]->ptr,"info-cache")) {
+        if (c->argc < 2) goto numargserr;
+        /* Reply format:
+         *   1.) master name
+         *   2.) 1.) info from master
+         *       2.) info from replica
+         *       .
+         *       .
+         *   3.) next master name ...
+         *   4.) 1.) info from master
+         *       2.) info from replica
+         *       .
+         *       .
+         */
+        dictType copy_keeper = instancesDictType;
+        copy_keeper.valDestructor = NULL;
+        dict *masters_local = NULL;
+        int needs_cleanup = 0;
+        if (c->argc == 2) {
+            masters_local = sentinel.masters;
+        } else {
+            masters_local = dictCreate(&copy_keeper, NULL);
+            needs_cleanup = 1;
+
+            for (int i = 2; i < c->argc; i++) {
+                sentinelRedisInstance *ri;
+                ri = sentinelGetMasterByName(c->argv[i]->ptr);
+                if (!ri) continue; /* ignore non-existing names */
+                dictAdd(masters_local, ri->name, ri);
+            }
+        }
+
+        /* Now we can iterate over individually requested masters the
+         * same way we iterate over the entire sentinel->masters dict. */
+        addReplyMultiBulkLen(c,dictSize(masters_local) * 2);
+
+        dictIterator  *di;
+        dictEntry *de;
+        di = dictGetIterator(masters_local);
+        while ((de = dictNext(di)) != NULL) {
+            sentinelRedisInstance *ri = dictGetVal(de);
+            addReplyBulkCBuffer(c,ri->name,strlen(ri->name));
+            addReplyMultiBulkLen(c,dictSize(ri->slaves) + 1); /* +1 for self */
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
+                if (sri->info)
+                    addReplyBulkCBuffer(c,sri->info,sdslen(sri->info));
+                else
+                    addReply(c,shared.nullbulk);
+            }
+            dictReleaseIterator(sdi);
+        }
+        dictReleaseIterator(di);
+        if (needs_cleanup) dictRelease(masters_local);
     } else {
         addReplyErrorFormat(c,"Unknown sentinel subcommand '%s'",
                                (char*)c->argv[1]->ptr);