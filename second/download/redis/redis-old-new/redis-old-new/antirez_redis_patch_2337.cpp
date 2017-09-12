@@ -348,6 +348,8 @@ static void sinterCommand(redisClient *c);
 static void sinterstoreCommand(redisClient *c);
 static void sunionCommand(redisClient *c);
 static void sunionstoreCommand(redisClient *c);
+static void sdiffCommand(redisClient *c);
+static void sdiffstoreCommand(redisClient *c);
 static void syncCommand(redisClient *c);
 static void flushdbCommand(redisClient *c);
 static void flushallCommand(redisClient *c);
@@ -391,6 +393,8 @@ static struct redisCommand cmdTable[] = {
     {"sinterstore",sinterstoreCommand,-3,REDIS_CMD_INLINE},
     {"sunion",sunionCommand,-2,REDIS_CMD_INLINE},
     {"sunionstore",sunionstoreCommand,-3,REDIS_CMD_INLINE},
+    {"sdiff",sdiffCommand,-2,REDIS_CMD_INLINE},
+    {"sdiffstore",sdiffstoreCommand,-3,REDIS_CMD_INLINE},
     {"smembers",sinterCommand,2,REDIS_CMD_INLINE},
     {"incrby",incrbyCommand,3,REDIS_CMD_INLINE},
     {"decrby",decrbyCommand,3,REDIS_CMD_INLINE},
@@ -3057,14 +3061,17 @@ static void sinterstoreCommand(redisClient *c) {
     sinterGenericCommand(c,c->argv+2,c->argc-2,c->argv[1]);
 }
 
-static void sunionGenericCommand(redisClient *c, robj **setskeys, int setsnum, robj *dstkey) {
+#define REDIS_OP_UNION 0
+#define REDIS_OP_DIFF 1
+
+static void sunionDiffGenericCommand(redisClient *c, robj **setskeys, int setsnum, robj *dstkey, int op) {
     dict **dv = zmalloc(sizeof(dict*)*setsnum);
     dictIterator *di;
     dictEntry *de;
-    robj *lenobj = NULL, *dstset = NULL;
+    robj *dstset = NULL;
     int j, cardinality = 0;
 
-    if (!dv) oom("sunionCommand");
+    if (!dv) oom("sunionDiffGenericCommand");
     for (j = 0; j < setsnum; j++) {
         robj *setobj;
 
@@ -3093,11 +3100,7 @@ static void sunionGenericCommand(redisClient *c, robj **setskeys, int setsnum, r
      * the intersection set size, so we use a trick, append an empty object
      * to the output list and save the pointer to later modify it with the
      * right length */
-    if (!dstkey) {
-        lenobj = createObject(REDIS_STRING,NULL);
-        addReply(c,lenobj);
-        decrRefCount(lenobj);
-    } else {
+    if (dstkey) {
         /* If we have a target key where to store the resulting set
          * create this key with an empty set inside */
         deleteKey(c->db,dstkey);
@@ -3119,22 +3122,39 @@ static void sunionGenericCommand(redisClient *c, robj **setskeys, int setsnum, r
 
             /* dictAdd will not add the same element multiple times */
             ele = dictGetEntryKey(de);
-            if (dictAdd(dstset->ptr,ele,NULL) == DICT_OK) {
-                incrRefCount(ele);
-                if (!dstkey) {
-                    addReplySds(c,sdscatprintf(sdsempty(),
-                            "$%d\r\n",sdslen(ele->ptr)));
-                    addReply(c,ele);
-                    addReply(c,shared.crlf);
+            if (op == REDIS_OP_UNION || j == 0) {
+                if (dictAdd(dstset->ptr,ele,NULL) == DICT_OK) {
+                    incrRefCount(ele);
                     cardinality++;
                 }
+            } else if (op == REDIS_OP_DIFF) {
+                if (dictDelete(dstset->ptr,ele) == DICT_OK) {
+                    cardinality--;
+                }
             }
         }
         dictReleaseIterator(di);
     }
 
+    /* Output the content of the resulting set, if not in STORE mode */
+    if (!dstkey) {
+        addReplySds(c,sdscatprintf(sdsempty(),"*%d\r\n",cardinality));
+        di = dictGetIterator(dstset->ptr);
+        if (!di) oom("dictGetIterator");
+        while((de = dictNext(di)) != NULL) {
+            robj *ele;
+
+            ele = dictGetEntryKey(de);
+            addReplySds(c,sdscatprintf(sdsempty(),
+                    "$%d\r\n",sdslen(ele->ptr)));
+            addReply(c,ele);
+            addReply(c,shared.crlf);
+        }
+        dictReleaseIterator(di);
+    }
+
+    /* Cleanup */
     if (!dstkey) {
-        lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",cardinality);
         decrRefCount(dstset);
     } else {
         addReply(c,shared.ok);
@@ -3144,11 +3164,19 @@ static void sunionGenericCommand(redisClient *c, robj **setskeys, int setsnum, r
 }
 
 static void sunionCommand(redisClient *c) {
-    sunionGenericCommand(c,c->argv+1,c->argc-1,NULL);
+    sunionDiffGenericCommand(c,c->argv+1,c->argc-1,NULL,REDIS_OP_UNION);
 }
 
 static void sunionstoreCommand(redisClient *c) {
-    sunionGenericCommand(c,c->argv+2,c->argc-2,c->argv[1]);
+    sunionDiffGenericCommand(c,c->argv+2,c->argc-2,c->argv[1],REDIS_OP_UNION);
+}
+
+static void sdiffCommand(redisClient *c) {
+    sunionDiffGenericCommand(c,c->argv+1,c->argc-1,NULL,REDIS_OP_DIFF);
+}
+
+static void sdiffstoreCommand(redisClient *c) {
+    sunionDiffGenericCommand(c,c->argv+2,c->argc-2,c->argv[1],REDIS_OP_DIFF);
 }
 
 static void flushdbCommand(redisClient *c) {