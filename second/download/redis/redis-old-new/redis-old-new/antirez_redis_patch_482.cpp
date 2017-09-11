@@ -550,8 +550,8 @@ void feedAppendOnlyFile(struct redisCommand *cmd, int dictid, robj **argv, int a
 
 /* In Redis commands are always executed in the context of a client, so in
  * order to load the append only file we need to create a fake client. */
-struct redisClient *createFakeClient(void) {
-    struct redisClient *c = zmalloc(sizeof(*c));
+struct client *createFakeClient(void) {
+    struct client *c = zmalloc(sizeof(*c));
 
     selectDb(c,0);
     c->fd = -1;
@@ -577,15 +577,15 @@ struct redisClient *createFakeClient(void) {
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
@@ -597,7 +597,7 @@ void freeFakeClient(struct redisClient *c) {
  * error (the append only file is zero-length) REDIS_ERR is returned. On
  * fatal error an error message is logged and the program exists. */
 int loadAppendOnlyFile(char *filename) {
-    struct redisClient *fakeClient;
+    struct client *fakeClient;
     FILE *fp = fopen(filename,"r");
     struct redis_stat sb;
     int old_aof_state = server.aof_state;
@@ -1297,7 +1297,7 @@ int rewriteAppendOnlyFileBackground(void) {
     return REDIS_OK; /* unreached */
 }
 
-void bgrewriteaofCommand(redisClient *c) {
+void bgrewriteaofCommand(client *c) {
     if (server.aof_child_pid != -1) {
         addReplyError(c,"Background append only file rewriting already in progress");
     } else if (server.rdb_child_pid != -1) {