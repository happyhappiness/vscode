@@ -42,7 +42,27 @@ static int checkStringLength(redisClient *c, long long size) {
     return REDIS_OK;
 }
 
-void setGenericCommand(redisClient *c, int nx, robj *key, robj *val, robj *expire, int unit) {
+/* The setGenericCommand() function implements the SET operation with different
+ * options and variants. This function is called in order to implement the
+ * following commands: SET, SETEX, PSETEX, SETNX.
+ *
+ * 'flags' changes the behavior of the command (NX or XX, see belove).
+ *
+ * 'expire' represents an expire to set in form of a Redis object as passed
+ * by the user. It is interpreted according to the specified 'unit'.
+ *
+ * 'ok_reply' and 'abort_reply' is what the function will reply to the client
+ * if the operation is performed, or when it is not because of NX or
+ * XX flags.
+ *
+ * If ok_reply is NULL "+OK" is used.
+ * If abort_reply is NULL, "$-1" is used. */
+
+#define REDIS_SET_NO_FLAGS 0
+#define REDIS_SET_NX (1<<0)     /* Set if key not exists. */
+#define REDIS_SET_XX (1<<1)     /* Set if key exists. */
+
+void setGenericCommand(redisClient *c, int flags, robj *key, robj *val, robj *expire, int unit, robj *ok_reply, robj *abort_reply) {
     long long milliseconds = 0; /* initialized to avoid any harmness warning */
 
     if (expire) {
@@ -55,8 +75,10 @@ void setGenericCommand(redisClient *c, int nx, robj *key, robj *val, robj *expir
         if (unit == UNIT_SECONDS) milliseconds *= 1000;
     }
 
-    if (nx && lookupKeyWrite(c->db,key) != NULL) {
-        addReply(c,shared.czero);
+    if ((flags & REDIS_SET_NX && lookupKeyWrite(c->db,key) != NULL) ||
+        (flags & REDIS_SET_XX && lookupKeyWrite(c->db,key) == NULL))
+    {
+        addReply(c, abort_reply ? abort_reply : shared.nullbulk);
         return;
     }
     setKey(c->db,key,val);
@@ -65,27 +87,55 @@ void setGenericCommand(redisClient *c, int nx, robj *key, robj *val, robj *expir
     notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"set",key,c->db->id);
     if (expire) notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,
         "expire",key,c->db->id);
-    addReply(c, nx ? shared.cone : shared.ok);
+    addReply(c, ok_reply ? ok_reply : shared.ok);
 }
 
+/* SET key value [NX] [XX] [EX <seconds>] [PX <milliseconds>] */
 void setCommand(redisClient *c) {
+    int j;
+    robj *expire = NULL;
+    int unit = UNIT_SECONDS;
+    int flags = REDIS_SET_NO_FLAGS;
+
+    for (j = 3; j < c->argc; j++) {
+        char *a = c->argv[j]->ptr;
+        robj *next = (j == c->argc-1) ? NULL : c->argv[j+1];
+
+        if (a[0] == 'n' && a[1] == 'x' && a[2] == '\0') {
+            flags |= REDIS_SET_NX;
+        } else if (a[0] == 'x' && a[1] == 'x' && a[2] == '\0') {
+            flags |= REDIS_SET_XX;
+        } else if (a[0] == 'e' && a[1] == 'x' && a[2] == '\0' && next) {
+            unit = UNIT_SECONDS;
+            expire = next;
+            j++;
+        } else if (a[0] == 'p' && a[1] == 'x' && a[2] == '\0' && next) {
+            unit = UNIT_MILLISECONDS;
+            expire = next;
+            j++;
+        } else {
+            addReply(c,shared.syntaxerr);
+            return;
+        }
+    }
+
     c->argv[2] = tryObjectEncoding(c->argv[2]);
-    setGenericCommand(c,0,c->argv[1],c->argv[2],NULL,0);
+    setGenericCommand(c,flags,c->argv[1],c->argv[2],expire,unit,NULL,NULL);
 }
 
 void setnxCommand(redisClient *c) {
     c->argv[2] = tryObjectEncoding(c->argv[2]);
-    setGenericCommand(c,1,c->argv[1],c->argv[2],NULL,0);
+    setGenericCommand(c,REDIS_SET_NX,c->argv[1],c->argv[2],NULL,0,shared.cone,shared.czero);
 }
 
 void setexCommand(redisClient *c) {
     c->argv[3] = tryObjectEncoding(c->argv[3]);
-    setGenericCommand(c,0,c->argv[1],c->argv[3],c->argv[2],UNIT_SECONDS);
+    setGenericCommand(c,REDIS_SET_NO_FLAGS,c->argv[1],c->argv[3],c->argv[2],UNIT_SECONDS,NULL,NULL);
 }
 
 void psetexCommand(redisClient *c) {
     c->argv[3] = tryObjectEncoding(c->argv[3]);
-    setGenericCommand(c,0,c->argv[1],c->argv[3],c->argv[2],UNIT_MILLISECONDS);
+    setGenericCommand(c,REDIS_SET_NO_FLAGS,c->argv[1],c->argv[3],c->argv[2],UNIT_MILLISECONDS,NULL,NULL);
 }
 
 int getGenericCommand(redisClient *c) {