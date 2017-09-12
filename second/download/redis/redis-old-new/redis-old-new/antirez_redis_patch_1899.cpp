@@ -119,16 +119,13 @@ void computeDatasetDigest(unsigned char *final) {
                 }
                 listTypeReleaseIterator(li);
             } else if (o->type == REDIS_SET) {
-                dict *set = o->ptr;
-                dictIterator *di = dictGetIterator(set);
-                dictEntry *de;
-
-                while((de = dictNext(di)) != NULL) {
-                    robj *eleobj = dictGetEntryKey(de);
-
-                    xorObjectDigest(digest,eleobj);
+                setTypeIterator *si = setTypeInitIterator(o);
+                robj *ele;
+                while((ele = setTypeNext(si)) != NULL) {
+                    xorObjectDigest(digest,ele);
+                    decrRefCount(ele);
                 }
-                dictReleaseIterator(di);
+                setTypeReleaseIterator(si);
             } else if (o->type == REDIS_ZSET) {
                 zset *zs = o->ptr;
                 dictIterator *di = dictGetIterator(zs->dict);
@@ -214,18 +211,18 @@ void debugCommand(redisClient *c) {
             char *strenc;
 
             strenc = strEncoding(val->encoding);
-            addReplySds(c,sdscatprintf(sdsempty(),
-                "+Value at:%p refcount:%d "
-                "encoding:%s serializedlength:%lld\r\n",
+            addReplyStatusFormat(c,
+                "Value at:%p refcount:%d "
+                "encoding:%s serializedlength:%lld",
                 (void*)val, val->refcount,
-                strenc, (long long) rdbSavedObjectLen(val,NULL)));
+                strenc, (long long) rdbSavedObjectLen(val,NULL));
         } else {
             vmpointer *vp = (vmpointer*) val;
-            addReplySds(c,sdscatprintf(sdsempty(),
-                "+Value swapped at: page %llu "
-                "using %llu pages\r\n",
+            addReplyStatusFormat(c,
+                "Value swapped at: page %llu "
+                "using %llu pages",
                 (unsigned long long) vp->page,
-                (unsigned long long) vp->usedpages));
+                (unsigned long long) vp->usedpages);
         }
     } else if (!strcasecmp(c->argv[1]->ptr,"swapin") && c->argc == 3) {
         lookupKeyRead(c->db,c->argv[2]);
@@ -236,7 +233,7 @@ void debugCommand(redisClient *c) {
         vmpointer *vp;
 
         if (!server.vm_enabled) {
-            addReplySds(c,sdsnew("-ERR Virtual Memory is disabled\r\n"));
+            addReplyError(c,"Virtual Memory is disabled");
             return;
         }
         if (!de) {
@@ -246,9 +243,9 @@ void debugCommand(redisClient *c) {
         val = dictGetEntryVal(de);
         /* Swap it */
         if (val->storage != REDIS_VM_MEMORY) {
-            addReplySds(c,sdsnew("-ERR This key is not in memory\r\n"));
+            addReplyError(c,"This key is not in memory");
         } else if (val->refcount != 1) {
-            addReplySds(c,sdsnew("-ERR Object is shared\r\n"));
+            addReplyError(c,"Object is shared");
         } else if ((vp = vmSwapObjectBlocking(val)) != NULL) {
             dictGetEntryVal(de) = vp;
             addReply(c,shared.ok);
@@ -277,18 +274,17 @@ void debugCommand(redisClient *c) {
         addReply(c,shared.ok);
     } else if (!strcasecmp(c->argv[1]->ptr,"digest") && c->argc == 2) {
         unsigned char digest[20];
-        sds d = sdsnew("+");
+        sds d = sdsempty();
         int j;
 
         computeDatasetDigest(digest);
         for (j = 0; j < 20; j++)
             d = sdscatprintf(d, "%02x",digest[j]);
-
-        d = sdscatlen(d,"\r\n",2);
-        addReplySds(c,d);
+        addReplyStatus(c,d);
+        sdsfree(d);
     } else {
-        addReplySds(c,sdsnew(
-            "-ERR Syntax error, try DEBUG [SEGFAULT|OBJECT <key>|SWAPIN <key>|SWAPOUT <key>|RELOAD]\r\n"));
+        addReplyError(c,
+            "Syntax error, try DEBUG [SEGFAULT|OBJECT <key>|SWAPIN <key>|SWAPOUT <key>|RELOAD]");
     }
 }
 