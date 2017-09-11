@@ -13,7 +13,6 @@ static int checkStringLength(redisClient *c, long long size) {
 }
 
 void setGenericCommand(redisClient *c, int nx, robj *key, robj *val, robj *expire) {
-    int retval;
     long seconds = 0; /* initialized to avoid an harmness warning */
 
     if (expire) {
@@ -25,21 +24,12 @@ void setGenericCommand(redisClient *c, int nx, robj *key, robj *val, robj *expir
         }
     }
 
-    retval = dbAdd(c->db,key,val);
-    if (retval == REDIS_ERR) {
-        if (!nx) {
-            dbReplace(c->db,key,val);
-            incrRefCount(val);
-        } else {
-            addReply(c,shared.czero);
-            return;
-        }
-    } else {
-        incrRefCount(val);
+    if (lookupKeyWrite(c->db,key) != NULL && nx) {
+        addReply(c,shared.czero);
+        return;
     }
-    signalModifiedKey(c->db,key);
+    setKey(c->db,key,val);
     server.dirty++;
-    removeExpire(c->db,key);
     if (expire) setExpire(c->db,key,time(NULL)+seconds);
     addReply(c, nx ? shared.cone : shared.ok);
 }
@@ -81,9 +71,7 @@ void getCommand(redisClient *c) {
 void getsetCommand(redisClient *c) {
     if (getGenericCommand(c) == REDIS_ERR) return;
     c->argv[2] = tryObjectEncoding(c->argv[2]);
-    dbReplace(c->db,c->argv[1],c->argv[2]);
-    incrRefCount(c->argv[2]);
-    signalModifiedKey(c->db,c->argv[1]);
+    setKey(c->db,c->argv[1],c->argv[2]);
     server.dirty++;
     removeExpire(c->db,c->argv[1]);
 }
@@ -138,7 +126,7 @@ void setbitCommand(redisClient *c) {
             robj *decoded = getDecodedObject(o);
             o = createStringObject(decoded->ptr, sdslen(decoded->ptr));
             decrRefCount(decoded);
-            dbReplace(c->db,c->argv[1],o);
+            dbOverwrite(c->db,c->argv[1],o);
         }
     }
 
@@ -236,7 +224,7 @@ void setrangeCommand(redisClient *c) {
             robj *decoded = getDecodedObject(o);
             o = createStringObject(decoded->ptr, sdslen(decoded->ptr));
             decrRefCount(decoded);
-            dbReplace(c->db,c->argv[1],o);
+            dbOverwrite(c->db,c->argv[1],o);
         }
     }
 
@@ -319,18 +307,15 @@ void msetGenericCommand(redisClient *c, int nx) {
                 busykeys++;
             }
         }
-    }
-    if (busykeys) {
-        addReply(c, shared.czero);
-        return;
+        if (busykeys) {
+            addReply(c, shared.czero);
+            return;
+        }
     }
 
     for (j = 1; j < c->argc; j += 2) {
         c->argv[j+1] = tryObjectEncoding(c->argv[j+1]);
-        dbReplace(c->db,c->argv[j],c->argv[j+1]);
-        incrRefCount(c->argv[j+1]);
-        removeExpire(c->db,c->argv[j]);
-        signalModifiedKey(c->db,c->argv[j]);
+        setKey(c->db,c->argv[j],c->argv[j+1]);
     }
     server.dirty += (c->argc-1)/2;
     addReply(c, nx ? shared.cone : shared.ok);
@@ -346,7 +331,7 @@ void msetnxCommand(redisClient *c) {
 
 void incrDecrCommand(redisClient *c, long long incr) {
     long long value, oldvalue;
-    robj *o;
+    robj *o, *new;
 
     o = lookupKeyWrite(c->db,c->argv[1]);
     if (o != NULL && checkType(c,o,REDIS_STRING)) return;
@@ -358,12 +343,15 @@ void incrDecrCommand(redisClient *c, long long incr) {
         addReplyError(c,"increment or decrement would overflow");
         return;
     }
-    o = createStringObjectFromLongLong(value);
-    dbReplace(c->db,c->argv[1],o);
+    new = createStringObjectFromLongLong(value);
+    if (o)
+        dbOverwrite(c->db,c->argv[1],new);
+    else
+        dbAdd(c->db,c->argv[1],new);
     signalModifiedKey(c->db,c->argv[1]);
     server.dirty++;
     addReply(c,shared.colon);
-    addReply(c,o);
+    addReply(c,new);
     addReply(c,shared.crlf);
 }
 
@@ -416,7 +404,7 @@ void appendCommand(redisClient *c) {
             robj *decoded = getDecodedObject(o);
             o = createStringObject(decoded->ptr, sdslen(decoded->ptr));
             decrRefCount(decoded);
-            dbReplace(c->db,c->argv[1],o);
+            dbOverwrite(c->db,c->argv[1],o);
         }
 
         /* Append the value */