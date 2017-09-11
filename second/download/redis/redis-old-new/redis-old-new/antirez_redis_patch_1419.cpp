@@ -1,3 +1,4 @@
+#include "fmacros.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
@@ -10,26 +11,89 @@
 
 #include "hiredis.h"
 
+enum connection_type {
+    CONN_TCP,
+    CONN_UNIX
+};
+
+struct config {
+    enum connection_type type;
+
+    struct {
+        const char *host;
+        int port;
+    } tcp;
+
+    struct {
+        const char *path;
+    } unix;
+};
+
 /* The following lines make up our testing "framework" :) */
 static int tests = 0, fails = 0;
 #define test(_s) { printf("#%02d ", ++tests); printf(_s); }
-#define test_cond(_c) if(_c) printf("PASSED\n"); else {printf("FAILED\n"); fails++;}
+#define test_cond(_c) if(_c) printf("\033[0;32mPASSED\033[0;0m\n"); else {printf("\033[0;31mFAILED\033[0;0m\n"); fails++;}
 
 static long long usec(void) {
     struct timeval tv;
     gettimeofday(&tv,NULL);
     return (((long long)tv.tv_sec)*1000000)+tv.tv_usec;
 }
 
-static int use_unix = 0;
-static redisContext *blocking_context = NULL;
-static void __connect(redisContext **target) {
-    *target = blocking_context = (use_unix ?
-        redisConnectUnix("/tmp/redis.sock") : redisConnect((char*)"127.0.0.1", 6379));
-    if (blocking_context->err) {
-        printf("Connection error: %s\n", blocking_context->errstr);
+static redisContext *select_database(redisContext *c) {
+    redisReply *reply;
+
+    /* Switch to DB 9 for testing, now that we know we can chat. */
+    reply = redisCommand(c,"SELECT 9");
+    assert(reply != NULL);
+    freeReplyObject(reply);
+
+    /* Make sure the DB is emtpy */
+    reply = redisCommand(c,"DBSIZE");
+    assert(reply != NULL);
+    if (reply->type == REDIS_REPLY_INTEGER && reply->integer == 0) {
+        /* Awesome, DB 9 is empty and we can continue. */
+        freeReplyObject(reply);
+    } else {
+        printf("Database #9 is not empty, test can not continue\n");
+        exit(1);
+    }
+
+    return c;
+}
+
+static void disconnect(redisContext *c) {
+    redisReply *reply;
+
+    /* Make sure we're on DB 9. */
+    reply = redisCommand(c,"SELECT 9");
+    assert(reply != NULL);
+    freeReplyObject(reply);
+    reply = redisCommand(c,"FLUSHDB");
+    assert(reply != NULL);
+    freeReplyObject(reply);
+
+    /* Free the context as well. */
+    redisFree(c);
+}
+
+static redisContext *connect(struct config config) {
+    redisContext *c = NULL;
+
+    if (config.type == CONN_TCP) {
+        c = redisConnect(config.tcp.host, config.tcp.port);
+    } else if (config.type == CONN_UNIX) {
+        c = redisConnectUnix(config.unix.path);
+    } else {
+        assert(NULL);
+    }
+
+    if (c->err) {
+        printf("Connection error: %s\n", c->errstr);
         exit(1);
     }
+
+    return select_database(c);
 }
 
 static void test_format_commands(void) {
@@ -78,29 +142,43 @@ static void test_format_commands(void) {
         len == 4+4+(3+2)+4+(1+2)+4+(1+2));
     free(cmd);
 
-    test("Format command with printf-delegation (long long): ");
-    len = redisFormatCommand(&cmd,"key:%08lld",1234ll);
-    test_cond(strncmp(cmd,"*1\r\n$12\r\nkey:00001234\r\n",len) == 0 &&
-        len == 4+5+(12+2));
-    free(cmd);
-
-    test("Format command with printf-delegation (float): ");
-    len = redisFormatCommand(&cmd,"v:%06.1f",12.34f);
-    test_cond(strncmp(cmd,"*1\r\n$8\r\nv:0012.3\r\n",len) == 0 &&
-        len == 4+4+(8+2));
-    free(cmd);
-
-    test("Format command with printf-delegation and extra interpolation: ");
-    len = redisFormatCommand(&cmd,"key:%d %b",1234,"foo",3);
-    test_cond(strncmp(cmd,"*2\r\n$8\r\nkey:1234\r\n$3\r\nfoo\r\n",len) == 0 &&
-        len == 4+4+(8+2)+4+(3+2));
-    free(cmd);
-
-    test("Format command with wrong printf format and extra interpolation: ");
-    len = redisFormatCommand(&cmd,"key:%08p %b",1234,"foo",3);
-    test_cond(strncmp(cmd,"*2\r\n$6\r\nkey:8p\r\n$3\r\nfoo\r\n",len) == 0 &&
-        len == 4+4+(6+2)+4+(3+2));
-    free(cmd);
+    /* Vararg width depends on the type. These tests make sure that the
+     * width is correctly determined using the format and subsequent varargs
+     * can correctly be interpolated. */
+#define INTEGER_WIDTH_TEST(fmt, type) do {                                                \
+    type value = 123;                                                                     \
+    test("Format command with printf-delegation (" #type "): ");                          \
+    len = redisFormatCommand(&cmd,"key:%08" fmt " str:%s", value, "hello");               \
+    test_cond(strncmp(cmd,"*2\r\n$12\r\nkey:00000123\r\n$9\r\nstr:hello\r\n",len) == 0 && \
+        len == 4+5+(12+2)+4+(9+2));                                                       \
+    free(cmd);                                                                            \
+} while(0)
+
+#define FLOAT_WIDTH_TEST(type) do {                                                       \
+    type value = 123.0;                                                                   \
+    test("Format command with printf-delegation (" #type "): ");                          \
+    len = redisFormatCommand(&cmd,"key:%08.3f str:%s", value, "hello");                   \
+    test_cond(strncmp(cmd,"*2\r\n$12\r\nkey:0123.000\r\n$9\r\nstr:hello\r\n",len) == 0 && \
+        len == 4+5+(12+2)+4+(9+2));                                                       \
+    free(cmd);                                                                            \
+} while(0)
+
+    INTEGER_WIDTH_TEST("d", int);
+    INTEGER_WIDTH_TEST("hhd", char);
+    INTEGER_WIDTH_TEST("hd", short);
+    INTEGER_WIDTH_TEST("ld", long);
+    INTEGER_WIDTH_TEST("lld", long long);
+    INTEGER_WIDTH_TEST("u", unsigned int);
+    INTEGER_WIDTH_TEST("hhu", unsigned char);
+    INTEGER_WIDTH_TEST("hu", unsigned short);
+    INTEGER_WIDTH_TEST("lu", unsigned long);
+    INTEGER_WIDTH_TEST("llu", unsigned long long);
+    FLOAT_WIDTH_TEST(float);
+    FLOAT_WIDTH_TEST(double);
+
+    test("Format command with invalid printf format: ");
+    len = redisFormatCommand(&cmd,"key:%08p %b",(void*)1234,"foo",3);
+    test_cond(len == -1);
 
     const char *argv[3];
     argv[0] = "SET";
@@ -122,42 +200,117 @@ static void test_format_commands(void) {
     free(cmd);
 }
 
-static void test_blocking_connection(void) {
+static void test_reply_reader(void) {
+    redisReader *reader;
+    void *reply;
+    int ret;
+
+    test("Error handling in reply parser: ");
+    reader = redisReaderCreate();
+    redisReaderFeed(reader,(char*)"@foo\r\n",6);
+    ret = redisReaderGetReply(reader,NULL);
+    test_cond(ret == REDIS_ERR &&
+              strcasecmp(reader->errstr,"Protocol error, got \"@\" as reply type byte") == 0);
+    redisReaderFree(reader);
+
+    /* when the reply already contains multiple items, they must be free'd
+     * on an error. valgrind will bark when this doesn't happen. */
+    test("Memory cleanup in reply parser: ");
+    reader = redisReaderCreate();
+    redisReaderFeed(reader,(char*)"*2\r\n",4);
+    redisReaderFeed(reader,(char*)"$5\r\nhello\r\n",11);
+    redisReaderFeed(reader,(char*)"@foo\r\n",6);
+    ret = redisReaderGetReply(reader,NULL);
+    test_cond(ret == REDIS_ERR &&
+              strcasecmp(reader->errstr,"Protocol error, got \"@\" as reply type byte") == 0);
+    redisReaderFree(reader);
+
+    test("Set error on nested multi bulks with depth > 2: ");
+    reader = redisReaderCreate();
+    redisReaderFeed(reader,(char*)"*1\r\n",4);
+    redisReaderFeed(reader,(char*)"*1\r\n",4);
+    redisReaderFeed(reader,(char*)"*1\r\n",4);
+    redisReaderFeed(reader,(char*)"*1\r\n",4);
+    ret = redisReaderGetReply(reader,NULL);
+    test_cond(ret == REDIS_ERR &&
+              strncasecmp(reader->errstr,"No support for",14) == 0);
+    redisReaderFree(reader);
+
+    test("Works with NULL functions for reply: ");
+    reader = redisReaderCreate();
+    reader->fn = NULL;
+    redisReaderFeed(reader,(char*)"+OK\r\n",5);
+    ret = redisReaderGetReply(reader,&reply);
+    test_cond(ret == REDIS_OK && reply == (void*)REDIS_REPLY_STATUS);
+    redisReaderFree(reader);
+
+    test("Works when a single newline (\\r\\n) covers two calls to feed: ");
+    reader = redisReaderCreate();
+    reader->fn = NULL;
+    redisReaderFeed(reader,(char*)"+OK\r",4);
+    ret = redisReaderGetReply(reader,&reply);
+    assert(ret == REDIS_OK && reply == NULL);
+    redisReaderFeed(reader,(char*)"\n",1);
+    ret = redisReaderGetReply(reader,&reply);
+    test_cond(ret == REDIS_OK && reply == (void*)REDIS_REPLY_STATUS);
+    redisReaderFree(reader);
+
+    test("Don't reset state after protocol error: ");
+    reader = redisReaderCreate();
+    reader->fn = NULL;
+    redisReaderFeed(reader,(char*)"x",1);
+    ret = redisReaderGetReply(reader,&reply);
+    assert(ret == REDIS_ERR);
+    ret = redisReaderGetReply(reader,&reply);
+    test_cond(ret == REDIS_ERR && reply == NULL);
+    redisReaderFree(reader);
+
+    /* Regression test for issue #45 on GitHub. */
+    test("Don't do empty allocation for empty multi bulk: ");
+    reader = redisReaderCreate();
+    redisReaderFeed(reader,(char*)"*0\r\n",4);
+    ret = redisReaderGetReply(reader,&reply);
+    test_cond(ret == REDIS_OK &&
+        ((redisReply*)reply)->type == REDIS_REPLY_ARRAY &&
+        ((redisReply*)reply)->elements == 0);
+    freeReplyObject(reply);
+    redisReaderFree(reader);
+}
+
+static void test_blocking_connection_errors(void) {
     redisContext *c;
-    redisReply *reply;
-    int major, minor;
 
     test("Returns error when host cannot be resolved: ");
     c = redisConnect((char*)"idontexist.local", 6379);
     test_cond(c->err == REDIS_ERR_OTHER &&
-        strcmp(c->errstr,"Can't resolve: idontexist.local") == 0);
+        (strcmp(c->errstr,"Name or service not known") == 0 ||
+         strcmp(c->errstr,"Can't resolve: idontexist.local") == 0));
     redisFree(c);
 
     test("Returns error when the port is not open: ");
-    c = redisConnect((char*)"localhost", 56380);
+    c = redisConnect((char*)"localhost", 1);
     test_cond(c->err == REDIS_ERR_IO &&
         strcmp(c->errstr,"Connection refused") == 0);
     redisFree(c);
 
-    __connect(&c);
+    test("Returns error when the unix socket path doesn't accept connections: ");
+    c = redisConnectUnix((char*)"/tmp/idontexist.sock");
+    test_cond(c->err == REDIS_ERR_IO); /* Don't care about the message... */
+    redisFree(c);
+}
+
+static void test_blocking_connection(struct config config) {
+    redisContext *c;
+    redisReply *reply;
+
+    c = connect(config);
+
     test("Is able to deliver commands: ");
     reply = redisCommand(c,"PING");
     test_cond(reply->type == REDIS_REPLY_STATUS &&
         strcasecmp(reply->str,"pong") == 0)
     freeReplyObject(reply);
 
-    /* Switch to DB 9 for testing, now that we know we can chat. */
-    reply = redisCommand(c,"SELECT 9");
-    freeReplyObject(reply);
-
-    /* Make sure the DB is emtpy */
-    reply = redisCommand(c,"DBSIZE");
-    if (reply->type != REDIS_REPLY_INTEGER || reply->integer != 0) {
-        printf("Database #9 is not empty, test can not continue\n");
-        exit(1);
-    }
-    freeReplyObject(reply);
-
     test("Is a able to send commands verbatim: ");
     reply = redisCommand(c,"SET foo bar");
     test_cond (reply->type == REDIS_REPLY_STATUS &&
@@ -221,6 +374,17 @@ static void test_blocking_connection(void) {
               strcasecmp(reply->element[1]->str,"pong") == 0);
     freeReplyObject(reply);
 
+    disconnect(c);
+}
+
+static void test_blocking_io_errors(struct config config) {
+    redisContext *c;
+    redisReply *reply;
+    void *_reply;
+    int major, minor;
+
+    /* Connect to target given by config. */
+    c = connect(config);
     {
         /* Find out Redis version to determine the path for the next test */
         const char *field = "redis_version:";
@@ -240,7 +404,7 @@ static void test_blocking_connection(void) {
         /* > 2.0 returns OK on QUIT and read() should be issued once more
          * to know the descriptor is at EOF. */
         test_cond(strcasecmp(reply->str,"OK") == 0 &&
-            redisGetReply(c,(void**)&reply) == REDIS_ERR);
+            redisGetReply(c,&_reply) == REDIS_ERR);
         freeReplyObject(reply);
     } else {
         test_cond(reply == NULL);
@@ -255,91 +419,20 @@ static void test_blocking_connection(void) {
         strcmp(c->errstr,"Server closed the connection") == 0);
     redisFree(c);
 
-    __connect(&c);
+    c = connect(config);
     test("Returns I/O error on socket timeout: ");
     struct timeval tv = { 0, 1000 };
     assert(redisSetTimeout(c,tv) == REDIS_OK);
-    test_cond(redisGetReply(c,(void**)&reply) == REDIS_ERR &&
+    test_cond(redisGetReply(c,&_reply) == REDIS_ERR &&
         c->err == REDIS_ERR_IO && errno == EAGAIN);
     redisFree(c);
-
-    /* Context should be connected */
-    __connect(&c);
 }
 
-static void test_reply_reader(void) {
-    void *reader;
-    void *reply;
-    char *err;
-    int ret;
-
-    test("Error handling in reply parser: ");
-    reader = redisReplyReaderCreate();
-    redisReplyReaderFeed(reader,(char*)"@foo\r\n",6);
-    ret = redisReplyReaderGetReply(reader,NULL);
-    err = redisReplyReaderGetError(reader);
-    test_cond(ret == REDIS_ERR &&
-              strcasecmp(err,"Protocol error, got \"@\" as reply type byte") == 0);
-    redisReplyReaderFree(reader);
-
-    /* when the reply already contains multiple items, they must be free'd
-     * on an error. valgrind will bark when this doesn't happen. */
-    test("Memory cleanup in reply parser: ");
-    reader = redisReplyReaderCreate();
-    redisReplyReaderFeed(reader,(char*)"*2\r\n",4);
-    redisReplyReaderFeed(reader,(char*)"$5\r\nhello\r\n",11);
-    redisReplyReaderFeed(reader,(char*)"@foo\r\n",6);
-    ret = redisReplyReaderGetReply(reader,NULL);
-    err = redisReplyReaderGetError(reader);
-    test_cond(ret == REDIS_ERR &&
-              strcasecmp(err,"Protocol error, got \"@\" as reply type byte") == 0);
-    redisReplyReaderFree(reader);
-
-    test("Set error on nested multi bulks with depth > 1: ");
-    reader = redisReplyReaderCreate();
-    redisReplyReaderFeed(reader,(char*)"*1\r\n",4);
-    redisReplyReaderFeed(reader,(char*)"*1\r\n",4);
-    redisReplyReaderFeed(reader,(char*)"*1\r\n",4);
-    ret = redisReplyReaderGetReply(reader,NULL);
-    err = redisReplyReaderGetError(reader);
-    test_cond(ret == REDIS_ERR &&
-              strncasecmp(err,"No support for",14) == 0);
-    redisReplyReaderFree(reader);
-
-    test("Works with NULL functions for reply: ");
-    reader = redisReplyReaderCreate();
-    redisReplyReaderSetReplyObjectFunctions(reader,NULL);
-    redisReplyReaderFeed(reader,(char*)"+OK\r\n",5);
-    ret = redisReplyReaderGetReply(reader,&reply);
-    test_cond(ret == REDIS_OK && reply == (void*)REDIS_REPLY_STATUS);
-    redisReplyReaderFree(reader);
-
-    test("Works when a single newline (\\r\\n) covers two calls to feed: ");
-    reader = redisReplyReaderCreate();
-    redisReplyReaderSetReplyObjectFunctions(reader,NULL);
-    redisReplyReaderFeed(reader,(char*)"+OK\r",4);
-    ret = redisReplyReaderGetReply(reader,&reply);
-    assert(ret == REDIS_OK && reply == NULL);
-    redisReplyReaderFeed(reader,(char*)"\n",1);
-    ret = redisReplyReaderGetReply(reader,&reply);
-    test_cond(ret == REDIS_OK && reply == (void*)REDIS_REPLY_STATUS);
-    redisReplyReaderFree(reader);
-
-    test("Properly reset state after protocol error: ");
-    reader = redisReplyReaderCreate();
-    redisReplyReaderSetReplyObjectFunctions(reader,NULL);
-    redisReplyReaderFeed(reader,(char*)"x",1);
-    ret = redisReplyReaderGetReply(reader,&reply);
-    assert(ret == REDIS_ERR);
-    ret = redisReplyReaderGetReply(reader,&reply);
-    test_cond(ret == REDIS_OK && reply == NULL)
-}
-
-static void test_throughput(void) {
+static void test_throughput(struct config config) {
+    redisContext *c = connect(config);
+    redisReply **replies;
     int i, num;
     long long t1, t2;
-    redisContext *c = blocking_context;
-    redisReply **replies;
 
     test("Throughput:\n");
     for (i = 0; i < 500; i++)
@@ -396,18 +489,8 @@ static void test_throughput(void) {
     for (i = 0; i < num; i++) freeReplyObject(replies[i]);
     free(replies);
     printf("\t(%dx LRANGE with 500 elements (pipelined): %.3fs)\n", num, (t2-t1)/1000000.0);
-}
 
-static void cleanup(void) {
-    redisContext *c = blocking_context;
-    redisReply *reply;
-
-    /* Make sure we're on DB 9 */
-    reply = redisCommand(c,"SELECT 9");
-    assert(reply != NULL); freeReplyObject(reply);
-    reply = redisCommand(c,"FLUSHDB");
-    assert(reply != NULL); freeReplyObject(reply);
-    redisFree(c);
+    disconnect(c);
 }
 
 // static long __test_callback_flags = 0;
@@ -429,7 +512,7 @@ static void cleanup(void) {
 // static redisContext *__connect_nonblock() {
 //     /* Reset callback flags */
 //     __test_callback_flags = 0;
-//     return redisConnectNonBlock("127.0.0.1", 6379, NULL);
+//     return redisConnectNonBlock("127.0.0.1", port, NULL);
 // }
 //
 // static void test_nonblocking_connection() {
@@ -510,23 +593,62 @@ static void cleanup(void) {
 // }
 
 int main(int argc, char **argv) {
-    if (argc > 1) {
-        if (strcmp(argv[1],"-s") == 0)
-            use_unix = 1;
+    struct config cfg = {
+        .tcp = {
+            .host = "127.0.0.1",
+            .port = 6379
+        },
+        .unix = {
+            .path = "/tmp/redis.sock"
+        }
+    };
+    int throughput = 1;
+
+    /* Ignore broken pipe signal (for I/O error tests). */
+    signal(SIGPIPE, SIG_IGN);
+
+    /* Parse command line options. */
+    argv++; argc--;
+    while (argc) {
+        if (argc >= 2 && !strcmp(argv[0],"-h")) {
+            argv++; argc--;
+            cfg.tcp.host = argv[0];
+        } else if (argc >= 2 && !strcmp(argv[0],"-p")) {
+            argv++; argc--;
+            cfg.tcp.port = atoi(argv[0]);
+        } else if (argc >= 2 && !strcmp(argv[0],"-s")) {
+            argv++; argc--;
+            cfg.unix.path = argv[0];
+        } else if (argc >= 1 && !strcmp(argv[0],"--skip-throughput")) {
+            throughput = 0;
+        } else {
+            fprintf(stderr, "Invalid argument: %s\n", argv[0]);
+            exit(1);
+        }
+        argv++; argc--;
     }
 
-    signal(SIGPIPE, SIG_IGN);
     test_format_commands();
-    test_blocking_connection();
     test_reply_reader();
-    // test_nonblocking_connection();
-    test_throughput();
-    cleanup();
+    test_blocking_connection_errors();
 
-    if (fails == 0) {
-        printf("ALL TESTS PASSED\n");
-    } else {
+    printf("\nTesting against TCP connection (%s:%d):\n", cfg.tcp.host, cfg.tcp.port);
+    cfg.type = CONN_TCP;
+    test_blocking_connection(cfg);
+    test_blocking_io_errors(cfg);
+    if (throughput) test_throughput(cfg);
+
+    printf("\nTesting against Unix socket connection (%s):\n", cfg.unix.path);
+    cfg.type = CONN_UNIX;
+    test_blocking_connection(cfg);
+    test_blocking_io_errors(cfg);
+    if (throughput) test_throughput(cfg);
+
+    if (fails) {
         printf("*** %d TESTS FAILED ***\n", fails);
+        return 1;
     }
+
+    printf("ALL TESTS PASSED\n");
     return 0;
 }