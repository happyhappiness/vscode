@@ -17,8 +17,6 @@ void setGenericCommand(redisClient *c, int nx, robj *key, robj *val, robj *expir
         }
     }
 
-    touchWatchedKey(c->db,key);
-    if (nx) deleteIfVolatile(c->db,key);
     retval = dbAdd(c->db,key,val);
     if (retval == REDIS_ERR) {
         if (!nx) {
@@ -31,6 +29,7 @@ void setGenericCommand(redisClient *c, int nx, robj *key, robj *val, robj *expir
     } else {
         incrRefCount(val);
     }
+    touchWatchedKey(c->db,key);
     server.dirty++;
     removeExpire(c->db,key);
     if (expire) setExpire(c->db,key,time(NULL)+seconds);
@@ -72,6 +71,7 @@ void getsetCommand(redisClient *c) {
     if (getGenericCommand(c) == REDIS_ERR) return;
     dbReplace(c->db,c->argv[1],c->argv[2]);
     incrRefCount(c->argv[2]);
+    touchWatchedKey(c->db,c->argv[1]);
     server.dirty++;
     removeExpire(c->db,c->argv[1]);
 }
@@ -120,6 +120,7 @@ void msetGenericCommand(redisClient *c, int nx) {
         dbReplace(c->db,c->argv[j],c->argv[j+1]);
         incrRefCount(c->argv[j+1]);
         removeExpire(c->db,c->argv[j]);
+        touchWatchedKey(c->db,c->argv[j]);
     }
     server.dirty += (c->argc-1)/2;
     addReply(c, nx ? shared.cone : shared.ok);
@@ -144,6 +145,7 @@ void incrDecrCommand(redisClient *c, long long incr) {
     value += incr;
     o = createStringObjectFromLongLong(value);
     dbReplace(c->db,c->argv[1],o);
+    touchWatchedKey(c->db,c->argv[1]);
     server.dirty++;
     addReply(c,shared.colon);
     addReply(c,o);
@@ -207,6 +209,7 @@ void appendCommand(redisClient *c) {
         }
         totlen = sdslen(o->ptr);
     }
+    touchWatchedKey(c->db,c->argv[1]);
     server.dirty++;
     addReplySds(c,sdscatprintf(sdsempty(),":%lu\r\n",(unsigned long)totlen));
 }
@@ -248,4 +251,13 @@ void substrCommand(redisClient *c) {
     decrRefCount(o);
 }
 
+void strlenCommand(redisClient *c) {
+    robj *o;
+
+    if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
+        checkType(c,o,REDIS_STRING)) return;
 
+    o = getDecodedObject(o);
+    addReplyLongLong(c,sdslen(o->ptr));
+    decrRefCount(o);
+}