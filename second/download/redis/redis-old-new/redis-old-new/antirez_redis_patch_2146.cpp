@@ -505,6 +505,7 @@ typedef struct zset {
 
 /* Our shared "common" objects */
 
+#define REDIS_SHARED_INTEGERS 10000
 struct sharedObjectsStruct {
     robj *crlf, *ok, *err, *emptybulk, *czero, *cone, *pong, *space,
     *colon, *nullbulk, *nullmultibulk, *queued,
@@ -513,7 +514,7 @@ struct sharedObjectsStruct {
     *select0, *select1, *select2, *select3, *select4,
     *select5, *select6, *select7, *select8, *select9,
     *messagebulk, *subscribebulk, *unsubscribebulk, *mbulk3,
-    *psubscribebulk, *punsubscribebulk;
+    *psubscribebulk, *punsubscribebulk, *integers[REDIS_SHARED_INTEGERS];
 } shared;
 
 /* Global vars that are actally used as constants. The following double
@@ -556,7 +557,7 @@ static robj *dupStringObject(robj *o);
 static void replicationFeedSlaves(list *slaves, int dictid, robj **argv, int argc);
 static void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv, int argc);
 static int syncWithMaster(void);
-static int tryObjectEncoding(robj *o);
+static robj *tryObjectEncoding(robj *o);
 static robj *getDecodedObject(robj *o);
 static int removeExpire(redisDb *db, robj *key);
 static int expireIfNeeded(redisDb *db, robj *key);
@@ -1484,6 +1485,8 @@ static void beforeSleep(struct aeEventLoop *eventLoop) {
 }
 
 static void createSharedObjects(void) {
+    int j;
+
     shared.crlf = createObject(REDIS_STRING,sdsnew("\r\n"));
     shared.ok = createObject(REDIS_STRING,sdsnew("+OK\r\n"));
     shared.err = createObject(REDIS_STRING,sdsnew("-ERR\r\n"));
@@ -1524,6 +1527,10 @@ static void createSharedObjects(void) {
     shared.psubscribebulk = createStringObject("$10\r\npsubscribe\r\n",17);
     shared.punsubscribebulk = createStringObject("$12\r\npunsubscribe\r\n",19);
     shared.mbulk3 = createStringObject("*3\r\n",4);
+    for (j = 0; j < REDIS_SHARED_INTEGERS; j++) {
+        shared.integers[j] = createObject(REDIS_STRING,(void*)(long)j);
+        shared.integers[j]->encoding = REDIS_ENCODING_INT;
+    }
 }
 
 static void appendServerSaveParams(time_t seconds, int changes) {
@@ -2277,7 +2284,7 @@ static int processCommand(redisClient *c) {
     }
     /* Let's try to encode the bulk object to save space. */
     if (cmd->flags & REDIS_CMD_BULK)
-        tryObjectEncoding(c->argv[c->argc-1]);
+        c->argv[c->argc-1] = tryObjectEncoding(c->argv[c->argc-1]);
 
     /* Check if the user is authenticated */
     if (server.requirepass && !c->authenticated && cmd->proc != authCommand) {
@@ -2963,29 +2970,35 @@ static int isStringRepresentableAsLong(sds s, long *longval) {
 }
 
 /* Try to encode a string object in order to save space */
-static int tryObjectEncoding(robj *o) {
+static robj *tryObjectEncoding(robj *o) {
     long value;
     sds s = o->ptr;
 
     if (o->encoding != REDIS_ENCODING_RAW)
-        return REDIS_ERR; /* Already encoded */
+        return o; /* Already encoded */
 
-    /* It's not save to encode shared objects: shared objects can be shared
+    /* It's not safe to encode shared objects: shared objects can be shared
      * everywhere in the "object space" of Redis. Encoded objects can only
      * appear as "values" (and not, for instance, as keys) */
-     if (o->refcount > 1) return REDIS_ERR;
+     if (o->refcount > 1) return o;
 
     /* Currently we try to encode only strings */
     redisAssert(o->type == REDIS_STRING);
 
     /* Check if we can represent this string as a long integer */
-    if (isStringRepresentableAsLong(s,&value) == REDIS_ERR) return REDIS_ERR;
+    if (isStringRepresentableAsLong(s,&value) == REDIS_ERR) return o;
 
     /* Ok, this object can be encoded */
-    o->encoding = REDIS_ENCODING_INT;
-    sdsfree(o->ptr);
-    o->ptr = (void*) value;
-    return REDIS_OK;
+    if (value >= 0 && value < REDIS_SHARED_INTEGERS) {
+        decrRefCount(o);
+        incrRefCount(shared.integers[value]);
+        return shared.integers[value];
+    } else {
+        o->encoding = REDIS_ENCODING_INT;
+        sdsfree(o->ptr);
+        o->ptr = (void*) value;
+        return o;
+    }
 }
 
 /* Get a decoded version of an encoded object (returned as a new object).
@@ -3603,7 +3616,7 @@ static robj *rdbLoadObject(int type, FILE *fp) {
     if (type == REDIS_STRING) {
         /* Read string value */
         if ((o = rdbLoadStringObject(fp)) == NULL) return NULL;
-        tryObjectEncoding(o);
+        o = tryObjectEncoding(o);
     } else if (type == REDIS_LIST || type == REDIS_SET) {
         /* Read list/set value */
         uint32_t listlen;
@@ -3619,7 +3632,7 @@ static robj *rdbLoadObject(int type, FILE *fp) {
             robj *ele;
 
             if ((ele = rdbLoadStringObject(fp)) == NULL) return NULL;
-            tryObjectEncoding(ele);
+            ele = tryObjectEncoding(ele);
             if (type == REDIS_LIST) {
                 listAddNodeTail((list*)o->ptr,ele);
             } else {
@@ -3640,7 +3653,7 @@ static robj *rdbLoadObject(int type, FILE *fp) {
             double *score = zmalloc(sizeof(double));
 
             if ((ele = rdbLoadStringObject(fp)) == NULL) return NULL;
-            tryObjectEncoding(ele);
+            ele = tryObjectEncoding(ele);
             if (rdbLoadDoubleValue(fp,score) == -1) return NULL;
             dictAdd(zs->dict,ele,score);
             zslInsert(zs->zsl,*score,ele);
@@ -3679,8 +3692,8 @@ static robj *rdbLoadObject(int type, FILE *fp) {
                 decrRefCount(key);
                 decrRefCount(val);
             } else {
-                tryObjectEncoding(key);
-                tryObjectEncoding(val);
+                key = tryObjectEncoding(key);
+                val = tryObjectEncoding(val);
                 dictAdd((dict*)o->ptr,key,val);
             }
         }
@@ -3906,7 +3919,7 @@ static void msetGenericCommand(redisClient *c, int nx) {
     for (j = 1; j < c->argc; j += 2) {
         int retval;
 
-        tryObjectEncoding(c->argv[j+1]);
+        c->argv[j+1] = tryObjectEncoding(c->argv[j+1]);
         retval = dictAdd(c->db->dict,c->argv[j],c->argv[j+1]);
         if (retval == DICT_ERR) {
             dictReplace(c->db->dict,c->argv[j],c->argv[j+1]);
@@ -3954,7 +3967,7 @@ static void incrDecrCommand(redisClient *c, long long incr) {
 
     value += incr;
     o = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",value));
-    tryObjectEncoding(o);
+    o = tryObjectEncoding(o);
     retval = dictAdd(c->db->dict,c->argv[1],o);
     if (retval == DICT_ERR) {
         dictReplace(c->db->dict,c->argv[1],o);
@@ -5977,7 +5990,7 @@ static void hsetCommand(redisClient *c) {
         if (zipmapLen(zm) > server.hash_max_zipmap_entries)
             convertToRealHash(o);
     } else {
-        tryObjectEncoding(c->argv[2]);
+        c->argv[2] = tryObjectEncoding(c->argv[2]);
         /* note that c->argv[3] is already encoded, as the latest arg
          * of a bulk command is always integer encoded if possible. */
         if (dictReplace(o->ptr,c->argv[2],c->argv[3])) {
@@ -6050,7 +6063,7 @@ static void hincrbyCommand(redisClient *c) {
 
         value += incr;
         hval = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",value));
-        tryObjectEncoding(hval);
+        hval = tryObjectEncoding(hval);
         if (dictReplace(o->ptr,c->argv[2],hval)) {
             incrRefCount(c->argv[2]);
         }
@@ -6235,8 +6248,8 @@ static void convertToRealHash(robj *o) {
 
         keyobj = createStringObject((char*)key,klen);
         valobj = createStringObject((char*)val,vlen);
-        tryObjectEncoding(keyobj);
-        tryObjectEncoding(valobj);
+        keyobj = tryObjectEncoding(keyobj);
+        valobj = tryObjectEncoding(valobj);
         dictAdd(dict,keyobj,valobj);
     }
     o->encoding = REDIS_ENCODING_HT;
@@ -7748,7 +7761,7 @@ int loadAppendOnlyFile(char *filename) {
         }
         /* Try object encoding */
         if (cmd->flags & REDIS_CMD_BULK)
-            tryObjectEncoding(argv[argc-1]);
+            argv[argc-1] = tryObjectEncoding(argv[argc-1]);
         /* Run the command in the context of a fake client */
         fakeClient->argc = argc;
         fakeClient->argv = argv;