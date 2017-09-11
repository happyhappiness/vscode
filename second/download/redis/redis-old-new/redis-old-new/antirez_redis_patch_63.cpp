@@ -11,6 +11,7 @@
 #include <limits.h>
 
 #include "hiredis.h"
+#include "net.h"
 
 enum connection_type {
     CONN_TCP,
@@ -29,7 +30,7 @@ struct config {
 
     struct {
         const char *path;
-    } unix;
+    } unix_sock;
 };
 
 /* The following lines make up our testing "framework" :) */
@@ -43,6 +44,13 @@ static long long usec(void) {
     return (((long long)tv.tv_sec)*1000000)+tv.tv_usec;
 }
 
+/* The assert() calls below have side effects, so we need assert()
+ * even if we are compiling without asserts (-DNDEBUG). */
+#ifdef NDEBUG
+#undef assert
+#define assert(e) (void)(e)
+#endif
+
 static redisContext *select_database(redisContext *c) {
     redisReply *reply;
 
@@ -51,7 +59,7 @@ static redisContext *select_database(redisContext *c) {
     assert(reply != NULL);
     freeReplyObject(reply);
 
-    /* Make sure the DB is empty */
+    /* Make sure the DB is emtpy */
     reply = redisCommand(c,"DBSIZE");
     assert(reply != NULL);
     if (reply->type == REDIS_REPLY_INTEGER && reply->integer == 0) {
@@ -89,10 +97,10 @@ static redisContext *connect(struct config config) {
     if (config.type == CONN_TCP) {
         c = redisConnect(config.tcp.host, config.tcp.port);
     } else if (config.type == CONN_UNIX) {
-        c = redisConnectUnix(config.unix.path);
+        c = redisConnectUnix(config.unix_sock.path);
     } else if (config.type == CONN_FD) {
         /* Create a dummy connection just to get an fd to inherit */
-        redisContext *dummy_ctx = redisConnectUnix(config.unix.path);
+        redisContext *dummy_ctx = redisConnectUnix(config.unix_sock.path);
         if (dummy_ctx) {
             int fd = disconnect(dummy_ctx, 1);
             printf("Connecting to inherited fd %d\n", fd);
@@ -107,6 +115,7 @@ static redisContext *connect(struct config config) {
         exit(1);
     } else if (c->err) {
         printf("Connection error: %s\n", c->errstr);
+        redisFree(c);
         exit(1);
     }
 
@@ -215,6 +224,22 @@ static void test_format_commands(void) {
     test_cond(strncmp(cmd,"*3\r\n$3\r\nSET\r\n$7\r\nfoo\0xxx\r\n$3\r\nbar\r\n",len) == 0 &&
         len == 4+4+(3+2)+4+(7+2)+4+(3+2));
     free(cmd);
+
+    sds sds_cmd;
+
+    sds_cmd = sdsempty();
+    test("Format command into sds by passing argc/argv without lengths: ");
+    len = redisFormatSdsCommandArgv(&sds_cmd,argc,argv,NULL);
+    test_cond(strncmp(sds_cmd,"*3\r\n$3\r\nSET\r\n$3\r\nfoo\r\n$3\r\nbar\r\n",len) == 0 &&
+        len == 4+4+(3+2)+4+(3+2)+4+(3+2));
+    sdsfree(sds_cmd);
+
+    sds_cmd = sdsempty();
+    test("Format command into sds by passing argc/argv with lengths: ");
+    len = redisFormatSdsCommandArgv(&sds_cmd,argc,argv,lens);
+    test_cond(strncmp(sds_cmd,"*3\r\n$3\r\nSET\r\n$7\r\nfoo\0xxx\r\n$3\r\nbar\r\n",len) == 0 &&
+        len == 4+4+(3+2)+4+(7+2)+4+(3+2));
+    sdsfree(sds_cmd);
 }
 
 static void test_append_formatted_commands(struct config config) {
@@ -318,16 +343,31 @@ static void test_reply_reader(void) {
     redisReaderFree(reader);
 }
 
+static void test_free_null(void) {
+    void *redisCtx = NULL;
+    void *reply = NULL;
+
+    test("Don't fail when redisFree is passed a NULL value: ");
+    redisFree(redisCtx);
+    test_cond(redisCtx == NULL);
+
+    test("Don't fail when freeReplyObject is passed a NULL value: ");
+    freeReplyObject(reply);
+    test_cond(reply == NULL);
+}
+
 static void test_blocking_connection_errors(void) {
     redisContext *c;
 
     test("Returns error when host cannot be resolved: ");
-    c = redisConnect((char*)"idontexist.local", 6379);
+    c = redisConnect((char*)"idontexist.test", 6379);
     test_cond(c->err == REDIS_ERR_OTHER &&
         (strcmp(c->errstr,"Name or service not known") == 0 ||
-         strcmp(c->errstr,"Can't resolve: idontexist.local") == 0 ||
+         strcmp(c->errstr,"Can't resolve: idontexist.test") == 0 ||
          strcmp(c->errstr,"nodename nor servname provided, or not known") == 0 ||
          strcmp(c->errstr,"No address associated with hostname") == 0 ||
+         strcmp(c->errstr,"Temporary failure in name resolution") == 0 ||
+         strcmp(c->errstr,"hostname nor servname provided, or not known") == 0 ||
          strcmp(c->errstr,"no address associated with name") == 0));
     redisFree(c);
 
@@ -337,7 +377,7 @@ static void test_blocking_connection_errors(void) {
         strcmp(c->errstr,"Connection refused") == 0);
     redisFree(c);
 
-    test("Returns error when the unix socket path doesn't accept connections: ");
+    test("Returns error when the unix_sock socket path doesn't accept connections: ");
     c = redisConnectUnix((char*)"/tmp/idontexist.sock");
     test_cond(c->err == REDIS_ERR_IO); /* Don't care about the message... */
     redisFree(c);
@@ -421,6 +461,52 @@ static void test_blocking_connection(struct config config) {
     disconnect(c, 0);
 }
 
+static void test_blocking_connection_timeouts(struct config config) {
+    redisContext *c;
+    redisReply *reply;
+    ssize_t s;
+    const char *cmd = "DEBUG SLEEP 3\r\n";
+    struct timeval tv;
+
+    c = connect(config);
+    test("Successfully completes a command when the timeout is not exceeded: ");
+    reply = redisCommand(c,"SET foo fast");
+    freeReplyObject(reply);
+    tv.tv_sec = 0;
+    tv.tv_usec = 10000;
+    redisSetTimeout(c, tv);
+    reply = redisCommand(c, "GET foo");
+    test_cond(reply != NULL && reply->type == REDIS_REPLY_STRING && memcmp(reply->str, "fast", 4) == 0);
+    freeReplyObject(reply);
+    disconnect(c, 0);
+
+    c = connect(config);
+    test("Does not return a reply when the command times out: ");
+    s = write(c->fd, cmd, strlen(cmd));
+    tv.tv_sec = 0;
+    tv.tv_usec = 10000;
+    redisSetTimeout(c, tv);
+    reply = redisCommand(c, "GET foo");
+    test_cond(s > 0 && reply == NULL && c->err == REDIS_ERR_IO && strcmp(c->errstr, "Resource temporarily unavailable") == 0);
+    freeReplyObject(reply);
+
+    test("Reconnect properly reconnects after a timeout: ");
+    redisReconnect(c);
+    reply = redisCommand(c, "PING");
+    test_cond(reply != NULL && reply->type == REDIS_REPLY_STATUS && strcmp(reply->str, "PONG") == 0);
+    freeReplyObject(reply);
+
+    test("Reconnect properly uses owned parameters: ");
+    config.tcp.host = "foo";
+    config.unix_sock.path = "foo";
+    redisReconnect(c);
+    reply = redisCommand(c, "PING");
+    test_cond(reply != NULL && reply->type == REDIS_REPLY_STATUS && strcmp(reply->str, "PONG") == 0);
+    freeReplyObject(reply);
+
+    disconnect(c, 0);
+}
+
 static void test_blocking_io_errors(struct config config) {
     redisContext *c;
     redisReply *reply;
@@ -444,7 +530,7 @@ static void test_blocking_io_errors(struct config config) {
 
     test("Returns I/O error when the connection is lost: ");
     reply = redisCommand(c,"QUIT");
-    if (major >= 2 && minor > 0) {
+    if (major > 2 || (major == 2 && minor > 0)) {
         /* > 2.0 returns OK on QUIT and read() should be issued once more
          * to know the descriptor is at EOF. */
         test_cond(strcasecmp(reply->str,"OK") == 0 &&
@@ -482,7 +568,8 @@ static void test_invalid_timeout_errors(struct config config) {
 
     c = redisConnectWithTimeout(config.tcp.host, config.tcp.port, config.tcp.timeout);
 
-    test_cond(c->err == REDIS_ERR_IO);
+    test_cond(c->err == REDIS_ERR_IO && strcmp(c->errstr, "Invalid timeout specified") == 0);
+    redisFree(c);
 
     test("Set error when an invalid timeout sec value is given to redisConnectWithTimeout: ");
 
@@ -491,8 +578,7 @@ static void test_invalid_timeout_errors(struct config config) {
 
     c = redisConnectWithTimeout(config.tcp.host, config.tcp.port, config.tcp.timeout);
 
-    test_cond(c->err == REDIS_ERR_IO);
-
+    test_cond(c->err == REDIS_ERR_IO && strcmp(c->errstr, "Invalid timeout specified") == 0);
     redisFree(c);
 }
 
@@ -666,7 +752,7 @@ int main(int argc, char **argv) {
             .host = "127.0.0.1",
             .port = 6379
         },
-        .unix = {
+        .unix_sock = {
             .path = "/tmp/redis.sock"
         }
     };
@@ -687,7 +773,7 @@ int main(int argc, char **argv) {
             cfg.tcp.port = atoi(argv[0]);
         } else if (argc >= 2 && !strcmp(argv[0],"-s")) {
             argv++; argc--;
-            cfg.unix.path = argv[0];
+            cfg.unix_sock.path = argv[0];
         } else if (argc >= 1 && !strcmp(argv[0],"--skip-throughput")) {
             throughput = 0;
         } else if (argc >= 1 && !strcmp(argv[0],"--skip-inherit-fd")) {
@@ -702,27 +788,31 @@ int main(int argc, char **argv) {
     test_format_commands();
     test_reply_reader();
     test_blocking_connection_errors();
+    test_free_null();
 
     printf("\nTesting against TCP connection (%s:%d):\n", cfg.tcp.host, cfg.tcp.port);
     cfg.type = CONN_TCP;
     test_blocking_connection(cfg);
+    test_blocking_connection_timeouts(cfg);
     test_blocking_io_errors(cfg);
     test_invalid_timeout_errors(cfg);
     test_append_formatted_commands(cfg);
     if (throughput) test_throughput(cfg);
 
-    printf("\nTesting against Unix socket connection (%s):\n", cfg.unix.path);
+    printf("\nTesting against Unix socket connection (%s):\n", cfg.unix_sock.path);
     cfg.type = CONN_UNIX;
     test_blocking_connection(cfg);
+    test_blocking_connection_timeouts(cfg);
     test_blocking_io_errors(cfg);
     if (throughput) test_throughput(cfg);
 
     if (test_inherit_fd) {
-        printf("\nTesting against inherited fd (%s):\n", cfg.unix.path);
+        printf("\nTesting against inherited fd (%s):\n", cfg.unix_sock.path);
         cfg.type = CONN_FD;
         test_blocking_connection(cfg);
     }
 
+
     if (fails) {
         printf("*** %d TESTS FAILED ***\n", fails);
         return 1;