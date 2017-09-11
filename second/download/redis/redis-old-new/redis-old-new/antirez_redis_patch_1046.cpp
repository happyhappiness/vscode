@@ -350,6 +350,25 @@ void scanCallback(void *privdata, const dictEntry *de) {
     if (val) listAddNodeTail(keys, val);
 }
 
+/* Try to parse a SCAN cursor stored ad object 'o':
+ * if the cursor is valid, store it as unsigned integer into *cursor and
+ * returns REDIS_OK. Otherwise return REDIS_ERR and send an error to the
+ * client. */
+int parseScanCursorOrReply(redisClient *c, robj *o, unsigned long *cursor) {
+    char *eptr;
+
+    /* Use strtoul() because we need an *unsigned* long, so
+     * getLongLongFromObject() does not cover the whole cursor space. */
+    errno = 0;
+    *cursor = strtoul(o->ptr, &eptr, 10);
+    if (isspace(((char*)o->ptr)[0]) || eptr[0] != '\0' || errno == ERANGE)
+    {
+        addReplyError(c, "invalid cursor");
+        return REDIS_ERR;
+    }
+    return REDIS_OK;
+}
+
 /* This command implements SCAN, HSCAN and SSCAN commands.
  * If object 'o' is passed, then it must be an Hash or Set object, otherwise
  * if 'o' is NULL the command will operate on the dictionary associated with
@@ -361,13 +380,12 @@ void scanCallback(void *privdata, const dictEntry *de) {
  *
  * In the case of an Hash object the function returns both the field and value
  * of every element on the Hash. */
-void scanGenericCommand(redisClient *c, robj *o) {
+void scanGenericCommand(redisClient *c, robj *o, unsigned long cursor) {
     int rv;
     int i, j;
-    char buf[REDIS_LONGSTR_SIZE], *eptr;
+    char buf[REDIS_LONGSTR_SIZE];
     list *keys = listCreate();
     listNode *node, *nextnode;
-    unsigned long cursor = 0;
     long count = 10;
     sds pat;
     int patlen, use_pattern = 0;
@@ -381,16 +399,6 @@ void scanGenericCommand(redisClient *c, robj *o) {
     /* Set i to the first option argument. The previous one is the cursor. */
     i = (o == NULL) ? 2 : 3; /* Skip the key argument if needed. */
 
-    /* Use strtoul() because we need an *unsigned* long, so
-     * getLongLongFromObject() does not cover the whole cursor space. */
-    errno = 0;
-    cursor = strtoul(c->argv[i-1]->ptr, &eptr, 10);
-    if (isspace(((char*)c->argv[i-1])[0]) || eptr[0] != '\0' || errno == ERANGE)
-    {
-        addReplyError(c, "invalid cursor");
-        goto cleanup;
-    }
-
     /* Step 1: Parse options. */
     while (i < c->argc) {
         j = c->argc - i;
@@ -548,7 +556,9 @@ void scanGenericCommand(redisClient *c, robj *o) {
 
 /* The SCAN command completely relies on scanGenericCommand. */
 void scanCommand(redisClient *c) {
-    scanGenericCommand(c,NULL);
+    unsigned long cursor;
+    if (parseScanCursorOrReply(c,c->argv[1],&cursor) == REDIS_ERR) return;
+    scanGenericCommand(c,NULL,cursor);
 }
 
 void dbsizeCommand(redisClient *c) {