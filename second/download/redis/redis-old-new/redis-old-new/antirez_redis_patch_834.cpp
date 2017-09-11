@@ -8,12 +8,14 @@
 #include <unistd.h>
 #include <signal.h>
 #include <errno.h>
+#include <limits.h>
 
 #include "hiredis.h"
 
 enum connection_type {
     CONN_TCP,
-    CONN_UNIX
+    CONN_UNIX,
+    CONN_FD
 };
 
 struct config {
@@ -22,6 +24,7 @@ struct config {
     struct {
         const char *host;
         int port;
+        struct timeval timeout;
     } tcp;
 
     struct {
@@ -62,7 +65,7 @@ static redisContext *select_database(redisContext *c) {
     return c;
 }
 
-static void disconnect(redisContext *c) {
+static int disconnect(redisContext *c, int keep_fd) {
     redisReply *reply;
 
     /* Make sure we're on DB 9. */
@@ -73,8 +76,11 @@ static void disconnect(redisContext *c) {
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
@@ -84,11 +90,22 @@ static redisContext *connect(struct config config) {
         c = redisConnect(config.tcp.host, config.tcp.port);
     } else if (config.type == CONN_UNIX) {
         c = redisConnectUnix(config.unix.path);
+    } else if (config.type == CONN_FD) {
+        /* Create a dummy connection just to get an fd to inherit */
+        redisContext *dummy_ctx = redisConnectUnix(config.unix.path);
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
         exit(1);
     }
@@ -125,13 +142,13 @@ static void test_format_commands(void) {
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
@@ -177,7 +194,7 @@ static void test_format_commands(void) {
     FLOAT_WIDTH_TEST(double);
 
     test("Format command with invalid printf format: ");
-    len = redisFormatCommand(&cmd,"key:%08p %b",(void*)1234,"foo",3);
+    len = redisFormatCommand(&cmd,"key:%08p %b",(void*)1234,"foo",(size_t)3);
     test_cond(len == -1);
 
     const char *argv[3];
@@ -200,10 +217,33 @@ static void test_format_commands(void) {
     free(cmd);
 }
 
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
+}
+
 static void test_reply_reader(void) {
     redisReader *reader;
     void *reply;
     int ret;
+    int i;
 
     test("Error handling in reply parser: ");
     reader = redisReaderCreate();
@@ -225,12 +265,13 @@ static void test_reply_reader(void) {
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
@@ -284,7 +325,10 @@ static void test_blocking_connection_errors(void) {
     c = redisConnect((char*)"idontexist.local", 6379);
     test_cond(c->err == REDIS_ERR_OTHER &&
         (strcmp(c->errstr,"Name or service not known") == 0 ||
-         strcmp(c->errstr,"Can't resolve: idontexist.local") == 0));
+         strcmp(c->errstr,"Can't resolve: idontexist.local") == 0 ||
+         strcmp(c->errstr,"nodename nor servname provided, or not known") == 0 ||
+         strcmp(c->errstr,"No address associated with hostname") == 0 ||
+         strcmp(c->errstr,"no address associated with name") == 0));
     redisFree(c);
 
     test("Returns error when the port is not open: ");
@@ -326,7 +370,7 @@ static void test_blocking_connection(struct config config) {
     freeReplyObject(reply);
 
     test("%%b String interpolation works: ");
-    reply = redisCommand(c,"SET %b %b","foo",3,"hello\x00world",11);
+    reply = redisCommand(c,"SET %b %b","foo",(size_t)3,"hello\x00world",(size_t)11);
     freeReplyObject(reply);
     reply = redisCommand(c,"GET foo");
     test_cond(reply->type == REDIS_REPLY_STRING &&
@@ -374,7 +418,7 @@ static void test_blocking_connection(struct config config) {
               strcasecmp(reply->element[1]->str,"pong") == 0);
     freeReplyObject(reply);
 
-    disconnect(c);
+    disconnect(c, 0);
 }
 
 static void test_blocking_io_errors(struct config config) {
@@ -428,6 +472,30 @@ static void test_blocking_io_errors(struct config config) {
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
+    test_cond(c->err == REDIS_ERR_IO);
+
+    test("Set error when an invalid timeout sec value is given to redisConnectWithTimeout: ");
+
+    config.tcp.timeout.tv_sec = (((LONG_MAX) - 999) / 1000) + 1;
+    config.tcp.timeout.tv_usec = 0;
+
+    c = redisConnectWithTimeout(config.tcp.host, config.tcp.port, config.tcp.timeout);
+
+    test_cond(c->err == REDIS_ERR_IO);
+
+    redisFree(c);
+}
+
 static void test_throughput(struct config config) {
     redisContext *c = connect(config);
     redisReply **replies;
@@ -490,7 +558,7 @@ static void test_throughput(struct config config) {
     free(replies);
     printf("\t(%dx LRANGE with 500 elements (pipelined): %.3fs)\n", num, (t2-t1)/1000000.0);
 
-    disconnect(c);
+    disconnect(c, 0);
 }
 
 // static long __test_callback_flags = 0;
@@ -603,6 +671,7 @@ int main(int argc, char **argv) {
         }
     };
     int throughput = 1;
+    int test_inherit_fd = 1;
 
     /* Ignore broken pipe signal (for I/O error tests). */
     signal(SIGPIPE, SIG_IGN);
@@ -621,6 +690,8 @@ int main(int argc, char **argv) {
             cfg.unix.path = argv[0];
         } else if (argc >= 1 && !strcmp(argv[0],"--skip-throughput")) {
             throughput = 0;
+        } else if (argc >= 1 && !strcmp(argv[0],"--skip-inherit-fd")) {
+            test_inherit_fd = 0;
         } else {
             fprintf(stderr, "Invalid argument: %s\n", argv[0]);
             exit(1);
@@ -636,6 +707,8 @@ int main(int argc, char **argv) {
     cfg.type = CONN_TCP;
     test_blocking_connection(cfg);
     test_blocking_io_errors(cfg);
+    test_invalid_timeout_errors(cfg);
+    test_append_formatted_commands(cfg);
     if (throughput) test_throughput(cfg);
 
     printf("\nTesting against Unix socket connection (%s):\n", cfg.unix.path);
@@ -644,6 +717,12 @@ int main(int argc, char **argv) {
     test_blocking_io_errors(cfg);
     if (throughput) test_throughput(cfg);
 
+    if (test_inherit_fd) {
+        printf("\nTesting against inherited fd (%s):\n", cfg.unix.path);
+        cfg.type = CONN_FD;
+        test_blocking_connection(cfg);
+    }
+
     if (fails) {
         printf("*** %d TESTS FAILED ***\n", fails);
         return 1;