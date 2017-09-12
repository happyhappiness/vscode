@@ -9683,6 +9683,40 @@ static void configSetCommand(redisClient *c) {
         server.masterauth = zstrdup(o->ptr);
     } else if (!strcasecmp(c->argv[2]->ptr,"maxmemory")) {
         server.maxmemory = strtoll(o->ptr, NULL, 10);
+    } else if (!strcasecmp(c->argv[2]->ptr,"save")) {
+        int vlen, j;
+        sds *v = sdssplitlen(o->ptr,sdslen(o->ptr)," ",1,&vlen);
+
+        /* Perform sanity check before setting the new config:
+         * - Even number of args
+         * - Seconds >= 1, changes >= 0 */
+        if (vlen & 1) {
+            sdsfreesplitres(v,vlen);
+            goto badfmt;
+        }
+        for (j = 0; j < vlen; j++) {
+            char *eptr;
+            long val;
+
+            val = strtoll(v[j], &eptr, 10);
+            if (eptr[0] != '\0' ||
+                ((j & 1) == 0 && val < 1) ||
+                ((j & 1) == 1 && val < 0)) {
+                sdsfreesplitres(v,vlen);
+                goto badfmt;
+            }
+        }
+        /* Finally set the new config */
+        resetServerSaveParams();
+        for (j = 0; j < vlen; j += 2) {
+            time_t seconds;
+            int changes;
+
+            seconds = strtoll(v[j],NULL,10);
+            changes = strtoll(v[j+1],NULL,10);
+            appendServerSaveParams(seconds, changes);
+        }
+        sdsfreesplitres(v,vlen);
     } else {
         addReplySds(c,sdscatprintf(sdsempty(),
             "-ERR not supported CONFIG parameter %s\r\n",
@@ -9692,6 +9726,14 @@ static void configSetCommand(redisClient *c) {
     }
     decrRefCount(o);
     addReply(c,shared.ok);
+    return;
+
+badfmt: /* Bad format errors */
+    addReplySds(c,sdscatprintf(sdsempty(),
+        "-ERR invalid argument '%s' for CONFIG SET '%s'\r\n",
+            (char*)o->ptr,
+            (char*)c->argv[2]->ptr));
+    decrRefCount(o);
 }
 
 static void configGetCommand(redisClient *c) {
@@ -9726,6 +9768,22 @@ static void configGetCommand(redisClient *c) {
         addReplyBulkCString(c,buf);
         matches++;
     }
+    if (stringmatch(pattern,"save",0)) {
+        sds buf = sdsempty();
+        int j;
+
+        for (j = 0; j < server.saveparamslen; j++) {
+            buf = sdscatprintf(buf,"%ld %d",
+                    server.saveparams[j].seconds,
+                    server.saveparams[j].changes);
+            if (j != server.saveparamslen-1)
+                buf = sdscatlen(buf," ",1);
+        }
+        addReplyBulkCString(c,"save");
+        addReplyBulkCString(c,buf);
+        sdsfree(buf);
+        matches++;
+    }
     decrRefCount(o);
     lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",matches*2);
 }