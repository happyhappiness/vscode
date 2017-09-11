@@ -259,6 +259,20 @@ void inputCatSds(void *result, const char *str) {
 void debugCommand(client *c) {
     if (!strcasecmp(c->argv[1]->ptr,"segfault")) {
         *((char*)-1) = 'x';
+    } else if (!strcasecmp(c->argv[1]->ptr,"restart") ||
+               !strcasecmp(c->argv[1]->ptr,"crash-and-recover"))
+    {
+        long long delay = 0;
+        if (c->argc >= 3) {
+            if (getLongLongFromObjectOrReply(c, c->argv[2], &delay, NULL)
+                != C_OK) return;
+            if (delay < 0) delay = 0;
+        }
+        int flags = !strcasecmp(c->argv[1]->ptr,"restart") ?
+            (RESTART_SERVER_GRACEFULLY|RESTART_SERVER_CONFIG_REWRITE) :
+             RESTART_SERVER_NONE;
+        restartServer(flags,delay);
+        addReplyError(c,"failed to restart the server. Check server logs.");
     } else if (!strcasecmp(c->argv[1]->ptr,"oom")) {
         void *ptr = zmalloc(ULONG_MAX); /* Should trigger an out of memory. */
         zfree(ptr);