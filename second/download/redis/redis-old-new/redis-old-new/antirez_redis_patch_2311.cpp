@@ -342,6 +342,7 @@ static void freeMemoryIfNeeded(void);
 static int processCommand(redisClient *c);
 static void setupSigSegvAction(void);
 static void rdbRemoveTempFile(pid_t childpid);
+static size_t stringObjectLen(robj *o);
 
 static void authCommand(redisClient *c);
 static void pingCommand(redisClient *c);
@@ -1412,7 +1413,8 @@ static void replicationFeedSlaves(list *slaves, struct redisCommand *cmd, int di
             robj *lenobj;
 
             lenobj = createObject(REDIS_STRING,
-                sdscatprintf(sdsempty(),"%d\r\n",sdslen(argv[j]->ptr)));
+                sdscatprintf(sdsempty(),"%d\r\n",
+                    stringObjectLen(argv[j])));
             lenobj->refcount = 0;
             outv[outc++] = lenobj;
         }
@@ -1919,6 +1921,17 @@ static int compareStringObjects(robj *a, robj *b) {
     }
 }
 
+static size_t stringObjectLen(robj *o) {
+    assert(o->type == REDIS_STRING);
+    if (o->encoding == REDIS_ENCODING_RAW) {
+        return sdslen(o->ptr);
+    } else {
+        char buf[32];
+
+        return snprintf(buf,32,"%ld",(long)o->ptr);
+    }
+}
+
 /*============================ DB saving/loading ============================ */
 
 static int rdbSaveType(FILE *fp, unsigned char type) {
@@ -3533,8 +3546,9 @@ static robj *lookupKeyByPattern(redisDb *db, robj *pattern, robj *subst) {
     int prefixlen, sublen, postfixlen;
     /* Expoit the internal sds representation to create a sds string allocated on the stack in order to make this function faster */
     struct {
-        long len;
-        long free;
+        int len;
+        unsigned short free;
+        unsigned short _len; /* not used here */
         char buf[REDIS_SORTKEY_MAX+1];
     } keyname;
 
@@ -3558,6 +3572,7 @@ static robj *lookupKeyByPattern(redisDb *db, robj *pattern, robj *subst) {
     memcpy(keyname.buf+prefixlen+sublen,p+1,postfixlen);
     keyname.buf[prefixlen+sublen+postfixlen] = '\0';
     keyname.len = prefixlen+sublen+postfixlen;
+    keyname._len = USHRT_MAX;
 
     keyobj.refcount = 1;
     keyobj.type = REDIS_STRING;