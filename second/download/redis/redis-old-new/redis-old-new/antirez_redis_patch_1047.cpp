@@ -364,7 +364,7 @@ void scanCallback(void *privdata, const dictEntry *de) {
 void scanGenericCommand(redisClient *c, robj *o) {
     int rv;
     int i, j;
-    char buf[REDIS_LONGSTR_SIZE];
+    char buf[REDIS_LONGSTR_SIZE], *eptr;
     list *keys = listCreate();
     listNode *node, *nextnode;
     unsigned long cursor = 0;
@@ -381,9 +381,12 @@ void scanGenericCommand(redisClient *c, robj *o) {
     /* Set i to the first option argument. The previous one is the cursor. */
     i = (o == NULL) ? 2 : 3; /* Skip the key argument if needed. */
 
-    /* Use sscanf because we need an *unsigned* long */
-    rv = sscanf(c->argv[i-1]->ptr, "%lu", &cursor);
-    if (rv != 1) {
+    /* Use strtoul() because we need an *unsigned* long, so
+     * getLongLongFromObject() does not cover the whole cursor space. */
+    errno = 0;
+    cursor = strtoul(c->argv[i-1]->ptr, &eptr, 10);
+    if (isspace(((char*)c->argv[i-1])[0]) || eptr[0] != '\0' || errno == ERANGE)
+    {
         addReplyError(c, "invalid cursor");
         goto cleanup;
     }