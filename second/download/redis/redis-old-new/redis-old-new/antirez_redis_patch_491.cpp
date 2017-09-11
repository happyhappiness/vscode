@@ -915,7 +915,7 @@ long long getInstantaneousMetric(int metric) {
  * The function gets the current time in milliseconds as argument since
  * it gets called multiple times in a loop, so calling gettimeofday() for
  * each iteration would be costly without any actual gain. */
-int clientsCronHandleTimeout(redisClient *c, mstime_t now_ms) {
+int clientsCronHandleTimeout(client *c, mstime_t now_ms) {
     time_t now = now_ms/1000;
 
     if (server.maxidletime &&
@@ -951,7 +951,7 @@ int clientsCronHandleTimeout(redisClient *c, mstime_t now_ms) {
  * free space not used, this function reclaims space if needed.
  *
  * The function always returns 0 as it never terminates the client. */
-int clientsCronResizeQueryBuffer(redisClient *c) {
+int clientsCronResizeQueryBuffer(client *c) {
     size_t querybuf_size = sdsAllocSize(c->querybuf);
     time_t idletime = server.unixtime - c->lastinteraction;
 
@@ -991,7 +991,7 @@ void clientsCron(void) {
                      numclients : CLIENTS_CRON_MIN_ITERATIONS;
 
     while(listLength(server.clients) && iterations--) {
-        redisClient *c;
+        client *c;
         listNode *head;
 
         /* Rotate the list, take the current head, process.
@@ -2071,20 +2071,20 @@ void alsoPropagate(struct redisCommand *cmd, int dbid, robj **argv, int argc,
 /* It is possible to call the function forceCommandPropagation() inside a
  * Redis command implementation in order to to force the propagation of a
  * specific command execution into AOF / Replication. */
-void forceCommandPropagation(redisClient *c, int flags) {
+void forceCommandPropagation(client *c, int flags) {
     if (flags & REDIS_PROPAGATE_REPL) c->flags |= REDIS_FORCE_REPL;
     if (flags & REDIS_PROPAGATE_AOF) c->flags |= REDIS_FORCE_AOF;
 }
 
 /* Avoid that the executed command is propagated at all. This way we
  * are free to just propagate what we want using the alsoPropagate()
  * API. */
-void preventCommandPropagation(redisClient *c) {
+void preventCommandPropagation(client *c) {
     c->flags |= REDIS_PREVENT_PROP;
 }
 
 /* Call() is the core of Redis execution of a command */
-void call(redisClient *c, int flags) {
+void call(client *c, int flags) {
     long long dirty, start, duration;
     int client_old_flags = c->flags;
 
@@ -2179,7 +2179,7 @@ void call(redisClient *c, int flags) {
  * If 1 is returned the client is still alive and valid and
  * other operations can be performed by the caller. Otherwise
  * if 0 is returned the client was destroyed (i.e. after QUIT). */
-int processCommand(redisClient *c) {
+int processCommand(client *c) {
     /* The QUIT command is handled separately. Normal command procs will
      * go through checking for replication and QUIT will cause trouble
      * when FORCE_REPLICATION is enabled and would be implemented in
@@ -2476,7 +2476,7 @@ int time_independent_strcmp(char *a, char *b) {
     return diff; /* If zero strings are the same. */
 }
 
-void authCommand(redisClient *c) {
+void authCommand(client *c) {
     if (!server.requirepass) {
         addReplyError(c,"Client sent AUTH, but no password is set");
     } else if (!time_independent_strcmp(c->argv[1]->ptr, server.requirepass)) {
@@ -2490,7 +2490,7 @@ void authCommand(redisClient *c) {
 
 /* The PING command. It works in a different way if the client is in
  * in Pub/Sub mode. */
-void pingCommand(redisClient *c) {
+void pingCommand(client *c) {
     /* The command takes zero or one arguments. */
     if (c->argc > 2) {
         addReplyErrorFormat(c,"wrong number of arguments for '%s' command",
@@ -2513,11 +2513,11 @@ void pingCommand(redisClient *c) {
     }
 }
 
-void echoCommand(redisClient *c) {
+void echoCommand(client *c) {
     addReplyBulk(c,c->argv[1]);
 }
 
-void timeCommand(redisClient *c) {
+void timeCommand(client *c) {
     struct timeval tv;
 
     /* gettimeofday() can only fail if &tv is a bad address so we
@@ -2529,7 +2529,7 @@ void timeCommand(redisClient *c) {
 }
 
 /* Helper function for addReplyCommand() to output flags. */
-int addReplyCommandFlag(redisClient *c, struct redisCommand *cmd, int f, char *reply) {
+int addReplyCommandFlag(client *c, struct redisCommand *cmd, int f, char *reply) {
     if (cmd->flags & f) {
         addReplyStatus(c, reply);
         return 1;
@@ -2538,7 +2538,7 @@ int addReplyCommandFlag(redisClient *c, struct redisCommand *cmd, int f, char *r
 }
 
 /* Output the representation of a Redis command. Used by the COMMAND command. */
-void addReplyCommand(redisClient *c, struct redisCommand *cmd) {
+void addReplyCommand(client *c, struct redisCommand *cmd) {
     if (!cmd) {
         addReply(c, shared.nullbulk);
     } else {
@@ -2575,7 +2575,7 @@ void addReplyCommand(redisClient *c, struct redisCommand *cmd) {
 }
 
 /* COMMAND <subcommand> <args> */
-void commandCommand(redisClient *c) {
+void commandCommand(client *c) {
     dictIterator *di;
     dictEntry *de;
 
@@ -3010,7 +3010,7 @@ sds genRedisInfoString(char *section) {
 
             listRewind(server.slaves,&li);
             while((ln = listNext(&li))) {
-                redisClient *slave = listNodeValue(ln);
+                client *slave = listNodeValue(ln);
                 char *state = NULL;
                 char ip[REDIS_IP_STR_LEN];
                 int port;
@@ -3113,7 +3113,7 @@ sds genRedisInfoString(char *section) {
     return info;
 }
 
-void infoCommand(redisClient *c) {
+void infoCommand(client *c) {
     char *section = c->argc == 2 ? c->argv[1]->ptr : "default";
 
     if (c->argc > 2) {
@@ -3123,7 +3123,7 @@ void infoCommand(redisClient *c) {
     addReplyBulkSds(c, genRedisInfoString(section));
 }
 
-void monitorCommand(redisClient *c) {
+void monitorCommand(client *c) {
     /* ignore MONITOR if already slave or in monitor mode */
     if (c->flags & REDIS_SLAVE) return;
 
@@ -3274,7 +3274,7 @@ int freeMemoryIfNeeded(void) {
 
         listRewind(server.slaves,&li);
         while((ln = listNext(&li))) {
-            redisClient *slave = listNodeValue(ln);
+            client *slave = listNodeValue(ln);
             unsigned long obuf_bytes = getClientOutputBufferMemoryUsage(slave);
             if (obuf_bytes > mem_used)
                 mem_used = 0;