@@ -1482,7 +1482,7 @@ void backgroundSaveDoneHandlerSocket(int exitcode, int bysignal) {
 
     listRewind(server.slaves,&li);
     while((ln = listNext(&li))) {
-        redisClient *slave = ln->value;
+        client *slave = ln->value;
 
         if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_END) {
             uint64_t j;
@@ -1566,7 +1566,7 @@ int rdbSaveToSlavesSockets(void) {
 
     listRewind(server.slaves,&li);
     while((ln = listNext(&li))) {
-        redisClient *slave = ln->value;
+        client *slave = ln->value;
 
         if (slave->replstate == REDIS_REPL_WAIT_BGSAVE_START) {
             clientids[numfds] = slave->id;
@@ -1672,7 +1672,7 @@ int rdbSaveToSlavesSockets(void) {
     return REDIS_OK; /* unreached */
 }
 
-void saveCommand(redisClient *c) {
+void saveCommand(client *c) {
     if (server.rdb_child_pid != -1) {
         addReplyError(c,"Background save already in progress");
         return;
@@ -1684,7 +1684,7 @@ void saveCommand(redisClient *c) {
     }
 }
 
-void bgsaveCommand(redisClient *c) {
+void bgsaveCommand(client *c) {
     if (server.rdb_child_pid != -1) {
         addReplyError(c,"Background save already in progress");
     } else if (server.aof_child_pid != -1) {