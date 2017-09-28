 /* ----------------------------------------------------------------------------
  * AOF loading
  * ------------------------------------------------------------------------- */
 
 /* In Redis commands are always executed in the context of a client, so in
  * order to load the append only file we need to create a fake client. */
-struct redisClient *createFakeClient(void) {
-    struct redisClient *c = zmalloc(sizeof(*c));
+struct client *createFakeClient(void) {
+    struct client *c = zmalloc(sizeof(*c));
 
     selectDb(c,0);
     c->fd = -1;
     c->name = NULL;
     c->querybuf = sdsempty();
     c->querybuf_peak = 0;
     c->argc = 0;
     c->argv = NULL;
     c->bufpos = 0;
     c->flags = 0;
-    c->btype = REDIS_BLOCKED_NONE;
+    c->btype = BLOCKED_NONE;
     /* We set the fake client as a slave waiting for the synchronization
      * so that Redis will not try to send replies to this client. */
-    c->replstate = REDIS_REPL_WAIT_BGSAVE_START;
+    c->replstate = SLAVE_STATE_WAIT_BGSAVE_START;
     c->reply = listCreate();
     c->reply_bytes = 0;
     c->obuf_soft_limit_reached_time = 0;
     c->watched_keys = listCreate();
     c->peerid = NULL;
     listSetFreeMethod(c->reply,decrRefCountVoid);
     listSetDupMethod(c->reply,dupClientReplyValue);
     initClientMultiState(c);
     return c;
 }
 
-void freeFakeClientArgv(struct redisClient *c) {
+void freeFakeClientArgv(struct client *c) {
     int j;
 
     for (j = 0; j < c->argc; j++)
         decrRefCount(c->argv[j]);
     zfree(c->argv);
 }
 
-void freeFakeClient(struct redisClient *c) {
+void freeFakeClient(struct client *c) {
     sdsfree(c->querybuf);
     listRelease(c->reply);
     listRelease(c->watched_keys);
     freeClientMultiState(c);
     zfree(c);
 }
 
-/* Replay the append log file. On success REDIS_OK is returned. On non fatal
- * error (the append only file is zero-length) REDIS_ERR is returned. On
+/* Replay the append log file. On success C_OK is returned. On non fatal
+ * error (the append only file is zero-length) C_ERR is returned. On
  * fatal error an error message is logged and the program exists. */
 int loadAppendOnlyFile(char *filename) {
-    struct redisClient *fakeClient;
+    struct client *fakeClient;
     FILE *fp = fopen(filename,"r");
     struct redis_stat sb;
     int old_aof_state = server.aof_state;
     long loops = 0;
     off_t valid_up_to = 0; /* Offset of the latest well-formed command loaded. */
 
     if (fp && redis_fstat(fileno(fp),&sb) != -1 && sb.st_size == 0) {
         server.aof_current_size = 0;
         fclose(fp);
-        return REDIS_ERR;
+        return C_ERR;
     }
 
     if (fp == NULL) {
-        redisLog(REDIS_WARNING,"Fatal error: can't open the append log file for reading: %s",strerror(errno));
+        serverLog(LL_WARNING,"Fatal error: can't open the append log file for reading: %s",strerror(errno));
         exit(1);
     }
 
     /* Temporarily disable AOF, to prevent EXEC from feeding a MULTI
      * to the same file we're about to read. */
-    server.aof_state = REDIS_AOF_OFF;
+    server.aof_state = AOF_OFF;
 
     fakeClient = createFakeClient();
     startLoading(fp);
 
     while(1) {
         int argc, j;
