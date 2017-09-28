  * if the operation is performed, or when it is not because of NX or
  * XX flags.
  *
  * If ok_reply is NULL "+OK" is used.
  * If abort_reply is NULL, "$-1" is used. */
 
-#define REDIS_SET_NO_FLAGS 0
-#define REDIS_SET_NX (1<<0)     /* Set if key not exists. */
-#define REDIS_SET_XX (1<<1)     /* Set if key exists. */
+#define OBJ_SET_NO_FLAGS 0
+#define OBJ_SET_NX (1<<0)     /* Set if key not exists. */
+#define OBJ_SET_XX (1<<1)     /* Set if key exists. */
+#define OBJ_SET_EX (1<<2)     /* Set if time in seconds is given */
+#define OBJ_SET_PX (1<<3)     /* Set if time in ms in given */
 
-void setGenericCommand(redisClient *c, int flags, robj *key, robj *val, robj *expire, int unit, robj *ok_reply, robj *abort_reply) {
+void setGenericCommand(client *c, int flags, robj *key, robj *val, robj *expire, int unit, robj *ok_reply, robj *abort_reply) {
     long long milliseconds = 0; /* initialized to avoid any harmness warning */
 
     if (expire) {
-        if (getLongLongFromObjectOrReply(c, expire, &milliseconds, NULL) != REDIS_OK)
+        if (getLongLongFromObjectOrReply(c, expire, &milliseconds, NULL) != C_OK)
             return;
         if (milliseconds <= 0) {
             addReplyErrorFormat(c,"invalid expire time in %s",c->cmd->name);
             return;
         }
         if (unit == UNIT_SECONDS) milliseconds *= 1000;
     }
 
-    if ((flags & REDIS_SET_NX && lookupKeyWrite(c->db,key) != NULL) ||
-        (flags & REDIS_SET_XX && lookupKeyWrite(c->db,key) == NULL))
+    if ((flags & OBJ_SET_NX && lookupKeyWrite(c->db,key) != NULL) ||
+        (flags & OBJ_SET_XX && lookupKeyWrite(c->db,key) == NULL))
     {
         addReply(c, abort_reply ? abort_reply : shared.nullbulk);
         return;
     }
     setKey(c->db,key,val);
     server.dirty++;
     if (expire) setExpire(c->db,key,mstime()+milliseconds);
-    notifyKeyspaceEvent(REDIS_NOTIFY_STRING,"set",key,c->db->id);
-    if (expire) notifyKeyspaceEvent(REDIS_NOTIFY_GENERIC,
+    notifyKeyspaceEvent(NOTIFY_STRING,"set",key,c->db->id);
+    if (expire) notifyKeyspaceEvent(NOTIFY_GENERIC,
         "expire",key,c->db->id);
     addReply(c, ok_reply ? ok_reply : shared.ok);
 }
 
 /* SET key value [NX] [XX] [EX <seconds>] [PX <milliseconds>] */
-void setCommand(redisClient *c) {
+void setCommand(client *c) {
     int j;
     robj *expire = NULL;
     int unit = UNIT_SECONDS;
-    int flags = REDIS_SET_NO_FLAGS;
+    int flags = OBJ_SET_NO_FLAGS;
 
     for (j = 3; j < c->argc; j++) {
         char *a = c->argv[j]->ptr;
         robj *next = (j == c->argc-1) ? NULL : c->argv[j+1];
 
         if ((a[0] == 'n' || a[0] == 'N') &&
-            (a[1] == 'x' || a[1] == 'X') && a[2] == '\0') {
-            flags |= REDIS_SET_NX;
+            (a[1] == 'x' || a[1] == 'X') && a[2] == '\0' &&
+            !(flags & OBJ_SET_XX))
+        {
+            flags |= OBJ_SET_NX;
         } else if ((a[0] == 'x' || a[0] == 'X') &&
-                   (a[1] == 'x' || a[1] == 'X') && a[2] == '\0') {
-            flags |= REDIS_SET_XX;
+                   (a[1] == 'x' || a[1] == 'X') && a[2] == '\0' &&
+                   !(flags & OBJ_SET_NX))
+        {
+            flags |= OBJ_SET_XX;
         } else if ((a[0] == 'e' || a[0] == 'E') &&
-                   (a[1] == 'x' || a[1] == 'X') && a[2] == '\0' && next) {
+                   (a[1] == 'x' || a[1] == 'X') && a[2] == '\0' &&
+                   !(flags & OBJ_SET_PX) && next)
+        {
+            flags |= OBJ_SET_EX;
             unit = UNIT_SECONDS;
             expire = next;
             j++;
         } else if ((a[0] == 'p' || a[0] == 'P') &&
-                   (a[1] == 'x' || a[1] == 'X') && a[2] == '\0' && next) {
+                   (a[1] == 'x' || a[1] == 'X') && a[2] == '\0' &&
+                   !(flags & OBJ_SET_EX) && next)
+        {
+            flags |= OBJ_SET_PX;
             unit = UNIT_MILLISECONDS;
             expire = next;
             j++;
         } else {
             addReply(c,shared.syntaxerr);
             return;
