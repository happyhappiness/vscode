@@ -6110,7 +6110,7 @@ static int hashExists(robj *o, robj *key) {
 
 /* Add an element, discard the old if the key already exists.
  * Return 0 on insert and 1 on update. */
-static int hashReplace(robj *o, robj *key, robj *value) {
+static int hashSet(robj *o, robj *key, robj *value) {
     int update = 0;
     if (o->encoding == REDIS_ENCODING_ZIPMAP) {
         key = getDecodedObject(key);
@@ -6247,7 +6247,7 @@ static void hsetCommand(redisClient *c) {
 
     if ((o = hashLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
     hashTryConversion(o,c->argv,2,3);
-    update = hashReplace(o,c->argv[2],c->argv[3]);
+    update = hashSet(o,c->argv[2],c->argv[3]);
     addReply(c, update ? shared.czero : shared.cone);
     server.dirty++;
 }
@@ -6260,7 +6260,7 @@ static void hsetnxCommand(redisClient *c) {
     if (hashExists(o, c->argv[2])) {
         addReply(c, shared.czero);
     } else {
-        hashReplace(o,c->argv[2],c->argv[3]);
+        hashSet(o,c->argv[2],c->argv[3]);
         addReply(c, shared.cone);
         server.dirty++;
     }
@@ -6278,7 +6278,7 @@ static void hmsetCommand(redisClient *c) {
     if ((o = hashLookupWriteOrCreate(c,c->argv[1])) == NULL) return;
     hashTryConversion(o,c->argv,2,c->argc-1);
     for (i = 2; i < c->argc; i += 2) {
-        hashReplace(o,c->argv[i],c->argv[i+1]);
+        hashSet(o,c->argv[i],c->argv[i+1]);
     }
     addReply(c, shared.ok);
 }
@@ -6308,7 +6308,7 @@ static void hincrbyCommand(redisClient *c) {
 
     value += incr;
     new = createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",value));
-    hashReplace(o,c->argv[2],new);
+    hashSet(o,c->argv[2],new);
     decrRefCount(new);
     addReplyLongLong(c,value);
     server.dirty++;