@@ -3108,6 +3108,17 @@ void RM_LogIOError(RedisModuleIO *io, const char *levelstr, const char *fmt, ...
  * Blocking clients from modules
  * -------------------------------------------------------------------------- */
 
+/* Readable handler for the awake pipe. We do nothing here, the awake bytes
+ * will be actually read in a more appropriate place in the
+ * moduleHandleBlockedClients() function that is where clients are actually
+ * served. */
+void moduleBlockedClientPipeReadable(aeEventLoop *el, int fd, void *privdata, int mask) {
+    UNUSED(el);
+    UNUSED(fd);
+    UNUSED(mask);
+    UNUSED(privdata);
+}
+
 /* This is called from blocked.c in order to unblock a client: may be called
  * for multiple reasons while the client is in the middle of being blocked
  * because the client is terminated, but is also called for cleanup when a
@@ -3171,6 +3182,9 @@ int RM_UnblockClient(RedisModuleBlockedClient *bc, void *privdata) {
     pthread_mutex_lock(&moduleUnblockedClientsMutex);
     bc->privdata = privdata;
     listAddNodeTail(moduleUnblockedClients,bc);
+    if (write(server.module_blocked_pipe[1],"A",1) != 1) {
+        /* Ignore the error, this is best-effort. */
+    }
     pthread_mutex_unlock(&moduleUnblockedClientsMutex);
     return REDISMODULE_OK;
 }
@@ -3195,6 +3209,10 @@ void moduleHandleBlockedClients(void) {
     RedisModuleBlockedClient *bc;
 
     pthread_mutex_lock(&moduleUnblockedClientsMutex);
+    /* Here we unblock all the pending clients blocked in modules operations
+     * so we can read every pending "awake byte" in the pipe. */
+    char buf[1];
+    while (read(server.module_blocked_pipe[0],buf,1) == 1);
     while (listLength(moduleUnblockedClients)) {
         ln = listFirst(moduleUnblockedClients);
         bc = ln->value;
@@ -3298,6 +3316,16 @@ void moduleInitModulesSystem(void) {
     server.loadmodule_queue = listCreate();
     modules = dictCreate(&modulesDictType,NULL);
     moduleRegisterCoreAPI();
+    if (pipe(server.module_blocked_pipe) == -1) {
+        serverLog(LL_WARNING,
+            "Can't create the pipe for module blocking commands: %s",
+            strerror(errno));
+        exit(1);
+    }
+    /* Make the pipe non blocking. This is just a best effort aware mechanism
+     * and we do not want to block not in the read nor in the write half. */
+    anetNonBlock(NULL,server.module_blocked_pipe[0]);
+    anetNonBlock(NULL,server.module_blocked_pipe[1]);
 }
 
 /* Load all the modules in the server.loadmodule_queue list, which is