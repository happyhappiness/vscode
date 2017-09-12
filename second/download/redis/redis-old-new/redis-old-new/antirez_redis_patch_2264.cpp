@@ -2451,7 +2451,7 @@ static int rdbSaveDoubleValue(FILE *fp, double val) {
         buf[0] = (val < 0) ? 255 : 254;
     } else {
         snprintf((char*)buf+1,sizeof(buf)-1,"%.17g",val);
-        buf[0] = strlen((char*)buf);
+        buf[0] = strlen((char*)buf+1);
         len = buf[0]+1;
     }
     if (fwrite(buf,len,1,fp) == 0) return -1;
@@ -2976,6 +2976,49 @@ static void mgetCommand(redisClient *c) {
     }
 }
 
+static void msetGenericCommand(redisClient *c, int nx) {
+    int j;
+
+    if ((c->argc % 2) == 0) {
+        addReplySds(c,sdsnew("-ERR wrong number of arguments\r\n"));
+        return;
+    }
+    /* Handle the NX flag. The MSETNX semantic is to return zero and don't
+     * set nothing at all if at least one already key exists. */
+    if (nx) {
+        for (j = 1; j < c->argc; j += 2) {
+            if (dictFind(c->db->dict,c->argv[j]) != NULL) {
+                addReply(c, shared.czero);
+                return;
+            }
+        }
+    }
+
+    for (j = 1; j < c->argc; j += 2) {
+        int retval;
+
+        retval = dictAdd(c->db->dict,c->argv[j],c->argv[j+1]);
+        if (retval == DICT_ERR) {
+            dictReplace(c->db->dict,c->argv[j],c->argv[j+1]);
+            incrRefCount(c->argv[j+1]);
+        } else {
+            incrRefCount(c->argv[j]);
+            incrRefCount(c->argv[j+1]);
+        }
+        removeExpire(c->db,c->argv[j]);
+    }
+    server.dirty += (c->argc-1)/2;
+    addReply(c, nx ? shared.cone : shared.ok);
+}
+
+static void msetCommand(redisClient *c) {
+    msetGenericCommand(c,0);
+}
+
+static void msetnxCommand(redisClient *c) {
+    msetGenericCommand(c,1);
+}
+
 static void incrDecrCommand(redisClient *c, long long incr) {
     long long value;
     int retval;
@@ -5094,49 +5137,6 @@ static void ttlCommand(redisClient *c) {
     addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",ttl));
 }
 
-static void msetGenericCommand(redisClient *c, int nx) {
-    int j;
-
-    if ((c->argc % 2) == 0) {
-        addReplySds(c,sdsnew("-ERR wrong number of arguments\r\n"));
-        return;
-    }
-    /* Handle the NX flag. The MSETNX semantic is to return zero and don't
-     * set nothing at all if at least one already key exists. */
-    if (nx) {
-        for (j = 1; j < c->argc; j += 2) {
-            if (dictFind(c->db->dict,c->argv[j]) != NULL) {
-                addReply(c, shared.czero);
-                return;
-            }
-        }
-    }
-
-    for (j = 1; j < c->argc; j += 2) {
-        int retval;
-
-        retval = dictAdd(c->db->dict,c->argv[j],c->argv[j+1]);
-        if (retval == DICT_ERR) {
-            dictReplace(c->db->dict,c->argv[j],c->argv[j+1]);
-            incrRefCount(c->argv[j+1]);
-        } else {
-            incrRefCount(c->argv[j]);
-            incrRefCount(c->argv[j+1]);
-        }
-        removeExpire(c->db,c->argv[j]);
-    }
-    server.dirty += (c->argc-1)/2;
-    addReply(c, nx ? shared.cone : shared.ok);
-}
-
-static void msetCommand(redisClient *c) {
-    msetGenericCommand(c,0);
-}
-
-static void msetnxCommand(redisClient *c) {
-    msetGenericCommand(c,1);
-}
-
 /* =============================== Replication  ============================= */
 
 static int syncWrite(int fd, char *ptr, ssize_t size, int timeout) {