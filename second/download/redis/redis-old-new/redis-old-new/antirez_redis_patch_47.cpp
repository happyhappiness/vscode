@@ -8,12 +8,15 @@
 #include <unistd.h>
 #include <signal.h>
 #include <errno.h>
+#include <limits.h>
 
 #include "hiredis.h"
+#include "net.h"
 
 enum connection_type {
     CONN_TCP,
-    CONN_UNIX
+    CONN_UNIX,
+    CONN_FD
 };
 
 struct config {
@@ -22,11 +25,12 @@ struct config {
     struct {
         const char *host;
         int port;
+        struct timeval timeout;
     } tcp;
 
     struct {
         const char *path;
-    } unix;
+    } unix_sock;
 };
 
 /* The following lines make up our testing "framework" :) */
@@ -40,6 +44,13 @@ static long long usec(void) {
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
 
@@ -62,7 +73,7 @@ static redisContext *select_database(redisContext *c) {
     return c;
 }
 
-static void disconnect(redisContext *c) {
+static int disconnect(redisContext *c, int keep_fd) {
     redisReply *reply;
 
     /* Make sure we're on DB 9. */
@@ -73,8 +84,11 @@ static void disconnect(redisContext *c) {
     assert(reply != NULL);
     freeReplyObject(reply);
 
-    /* Free the context as well. */
+    /* Free the context as well, but keep the fd if requested. */
+    if (keep_fd)
+        return redisFreeKeepFd(c);
     redisFree(c);
+    return -1;
 }
 
 static redisContext *connect(struct config config) {
@@ -83,13 +97,25 @@ static redisContext *connect(struct config config) {
     if (config.type == CONN_TCP) {
         c = redisConnect(config.tcp.host, config.tcp.port);
     } else if (config.type == CONN_UNIX) {
-        c = redisConnectUnix(config.unix.path);
+        c = redisConnectUnix(config.unix_sock.path);
+    } else if (config.type == CONN_FD) {
+        /* Create a dummy connection just to get an fd to inherit */
+        redisContext *dummy_ctx = redisConnectUnix(config.unix_sock.path);
+        if (dummy_ctx) {
+            int fd = disconnect(dummy_ctx, 1);
+            printf("Connecting to inherited fd %d\n", fd);
+            c = redisConnectFd(fd);
+        }
     } else {
         assert(NULL);
     }
 
-    if (c->err) {
+    if (c == NULL) {
+        printf("Connection error: can't allocate redis context\n");
+        exit(1);
+    } else if (c->err) {
         printf("Connection error: %s\n", c->errstr);
+        redisFree(c);
         exit(1);
     }
 
@@ -125,13 +151,13 @@ static void test_format_commands(void) {
     free(cmd);
 
     test("Format command with %%b string interpolation: ");
-    len = redisFormatCommand(&cmd,"SET %b %b","foo",3,"b\0r",3);
+    len = redisFormatCommand(&cmd,"SET %b %b","foo",(size_t)3,"b\0r",(size_t)3);
     test_cond(strncmp(cmd,"*3\r\n$3\r\nSET\r\n$3\r\nfoo\r\n$3\r\nb\0r\r\n",len) == 0 &&
         len == 4+4+(3+2)+4+(3+2)+4+(3+2));
     free(cmd);
 
     test("Format command with %%b and an empty string: ");
-    len = redisFormatCommand(&cmd,"SET %b %b","foo",3,"",0);
+    len = redisFormatCommand(&cmd,"SET %b %b","foo",(size_t)3,"",(size_t)0);
     test_cond(strncmp(cmd,"*3\r\n$3\r\nSET\r\n$3\r\nfoo\r\n$0\r\n\r\n",len) == 0 &&
         len == 4+4+(3+2)+4+(3+2)+4+(0+2));
     free(cmd);
@@ -177,7 +203,7 @@ static void test_format_commands(void) {
     FLOAT_WIDTH_TEST(double);
 
     test("Format command with invalid printf format: ");
-    len = redisFormatCommand(&cmd,"key:%08p %b",(void*)1234,"foo",3);
+    len = redisFormatCommand(&cmd,"key:%08p %b",(void*)1234,"foo",(size_t)3);
     test_cond(len == -1);
 
     const char *argv[3];
@@ -198,12 +224,51 @@ static void test_format_commands(void) {
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
+}
+
+static void test_append_formatted_commands(struct config config) {
+    redisContext *c;
+    redisReply *reply;
+    char *cmd;
+    int len;
+
+    c = connect(config);
+
+    test("Append format command: ");
+
+    len = redisFormatCommand(&cmd, "SET foo bar");
+
+    test_cond(redisAppendFormattedCommand(c, cmd, len) == REDIS_OK);
+
+    assert(redisGetReply(c, (void*)&reply) == REDIS_OK);
+
+    free(cmd);
+    freeReplyObject(reply);
+
+    disconnect(c, 0);
 }
 
 static void test_reply_reader(void) {
     redisReader *reader;
     void *reply;
     int ret;
+    int i;
 
     test("Error handling in reply parser: ");
     reader = redisReaderCreate();
@@ -225,12 +290,13 @@ static void test_reply_reader(void) {
               strcasecmp(reader->errstr,"Protocol error, got \"@\" as reply type byte") == 0);
     redisReaderFree(reader);
 
-    test("Set error on nested multi bulks with depth > 2: ");
+    test("Set error on nested multi bulks with depth > 7: ");
     reader = redisReaderCreate();
-    redisReaderFeed(reader,(char*)"*1\r\n",4);
-    redisReaderFeed(reader,(char*)"*1\r\n",4);
-    redisReaderFeed(reader,(char*)"*1\r\n",4);
-    redisReaderFeed(reader,(char*)"*1\r\n",4);
+
+    for (i = 0; i < 9; i++) {
+        redisReaderFeed(reader,(char*)"*1\r\n",4);
+    }
+
     ret = redisReaderGetReply(reader,NULL);
     test_cond(ret == REDIS_ERR &&
               strncasecmp(reader->errstr,"No support for",14) == 0);
@@ -277,14 +343,32 @@ static void test_reply_reader(void) {
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
-         strcmp(c->errstr,"Can't resolve: idontexist.local") == 0));
+         strcmp(c->errstr,"Can't resolve: idontexist.test") == 0 ||
+         strcmp(c->errstr,"nodename nor servname provided, or not known") == 0 ||
+         strcmp(c->errstr,"No address associated with hostname") == 0 ||
+         strcmp(c->errstr,"Temporary failure in name resolution") == 0 ||
+         strcmp(c->errstr,"hostname nor servname provided, or not known") == 0 ||
+         strcmp(c->errstr,"no address associated with name") == 0));
     redisFree(c);
 
     test("Returns error when the port is not open: ");
@@ -293,7 +377,7 @@ static void test_blocking_connection_errors(void) {
         strcmp(c->errstr,"Connection refused") == 0);
     redisFree(c);
 
-    test("Returns error when the unix socket path doesn't accept connections: ");
+    test("Returns error when the unix_sock socket path doesn't accept connections: ");
     c = redisConnectUnix((char*)"/tmp/idontexist.sock");
     test_cond(c->err == REDIS_ERR_IO); /* Don't care about the message... */
     redisFree(c);
@@ -326,7 +410,7 @@ static void test_blocking_connection(struct config config) {
     freeReplyObject(reply);
 
     test("%%b String interpolation works: ");
-    reply = redisCommand(c,"SET %b %b","foo",3,"hello\x00world",11);
+    reply = redisCommand(c,"SET %b %b","foo",(size_t)3,"hello\x00world",(size_t)11);
     freeReplyObject(reply);
     reply = redisCommand(c,"GET foo");
     test_cond(reply->type == REDIS_REPLY_STRING &&
@@ -374,7 +458,53 @@ static void test_blocking_connection(struct config config) {
               strcasecmp(reply->element[1]->str,"pong") == 0);
     freeReplyObject(reply);
 
-    disconnect(c);
+    disconnect(c, 0);
+}
+
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
 }
 
 static void test_blocking_io_errors(struct config config) {
@@ -400,7 +530,7 @@ static void test_blocking_io_errors(struct config config) {
 
     test("Returns I/O error when the connection is lost: ");
     reply = redisCommand(c,"QUIT");
-    if (major >= 2 && minor > 0) {
+    if (major > 2 || (major == 2 && minor > 0)) {
         /* > 2.0 returns OK on QUIT and read() should be issued once more
          * to know the descriptor is at EOF. */
         test_cond(strcasecmp(reply->str,"OK") == 0 &&
@@ -428,6 +558,30 @@ static void test_blocking_io_errors(struct config config) {
     redisFree(c);
 }
 
+static void test_invalid_timeout_errors(struct config config) {
+    redisContext *c;
+
+    test("Set error when an invalid timeout usec value is given to redisConnectWithTimeout: ");
+
+    config.tcp.timeout.tv_sec = 0;
+    config.tcp.timeout.tv_usec = 10000001;
+
+    c = redisConnectWithTimeout(config.tcp.host, config.tcp.port, config.tcp.timeout);
+
+    test_cond(c->err == REDIS_ERR_IO && strcmp(c->errstr, "Invalid timeout specified") == 0);
+    redisFree(c);
+
+    test("Set error when an invalid timeout sec value is given to redisConnectWithTimeout: ");
+
+    config.tcp.timeout.tv_sec = (((LONG_MAX) - 999) / 1000) + 1;
+    config.tcp.timeout.tv_usec = 0;
+
+    c = redisConnectWithTimeout(config.tcp.host, config.tcp.port, config.tcp.timeout);
+
+    test_cond(c->err == REDIS_ERR_IO && strcmp(c->errstr, "Invalid timeout specified") == 0);
+    redisFree(c);
+}
+
 static void test_throughput(struct config config) {
     redisContext *c = connect(config);
     redisReply **replies;
@@ -490,7 +644,7 @@ static void test_throughput(struct config config) {
     free(replies);
     printf("\t(%dx LRANGE with 500 elements (pipelined): %.3fs)\n", num, (t2-t1)/1000000.0);
 
-    disconnect(c);
+    disconnect(c, 0);
 }
 
 // static long __test_callback_flags = 0;
@@ -598,11 +752,12 @@ int main(int argc, char **argv) {
             .host = "127.0.0.1",
             .port = 6379
         },
-        .unix = {
+        .unix_sock = {
             .path = "/tmp/redis.sock"
         }
     };
     int throughput = 1;
+    int test_inherit_fd = 1;
 
     /* Ignore broken pipe signal (for I/O error tests). */
     signal(SIGPIPE, SIG_IGN);
@@ -618,9 +773,11 @@ int main(int argc, char **argv) {
             cfg.tcp.port = atoi(argv[0]);
         } else if (argc >= 2 && !strcmp(argv[0],"-s")) {
             argv++; argc--;
-            cfg.unix.path = argv[0];
+            cfg.unix_sock.path = argv[0];
         } else if (argc >= 1 && !strcmp(argv[0],"--skip-throughput")) {
             throughput = 0;
+        } else if (argc >= 1 && !strcmp(argv[0],"--skip-inherit-fd")) {
+            test_inherit_fd = 0;
         } else {
             fprintf(stderr, "Invalid argument: %s\n", argv[0]);
             exit(1);
@@ -631,19 +788,31 @@ int main(int argc, char **argv) {
     test_format_commands();
     test_reply_reader();
     test_blocking_connection_errors();
+    test_free_null();
 
     printf("\nTesting against TCP connection (%s:%d):\n", cfg.tcp.host, cfg.tcp.port);
     cfg.type = CONN_TCP;
     test_blocking_connection(cfg);
+    test_blocking_connection_timeouts(cfg);
     test_blocking_io_errors(cfg);
+    test_invalid_timeout_errors(cfg);
+    test_append_formatted_commands(cfg);
     if (throughput) test_throughput(cfg);
 
-    printf("\nTesting against Unix socket connection (%s):\n", cfg.unix.path);
+    printf("\nTesting against Unix socket connection (%s):\n", cfg.unix_sock.path);
     cfg.type = CONN_UNIX;
     test_blocking_connection(cfg);
+    test_blocking_connection_timeouts(cfg);
     test_blocking_io_errors(cfg);
     if (throughput) test_throughput(cfg);
 
+    if (test_inherit_fd) {
+        printf("\nTesting against inherited fd (%s):\n", cfg.unix_sock.path);
+        cfg.type = CONN_FD;
+        test_blocking_connection(cfg);
+    }
+
+
     if (fails) {
         printf("*** %d TESTS FAILED ***\n", fails);
         return 1;