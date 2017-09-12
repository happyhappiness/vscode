@@ -6,6 +6,7 @@
 #include <assert.h>
 #include <unistd.h>
 #include <signal.h>
+#include <errno.h>
 
 #include "hiredis.h"
 
@@ -31,7 +32,7 @@ static void __connect(redisContext **target) {
     }
 }
 
-static void test_format_commands() {
+static void test_format_commands(void) {
     char *cmd;
     int len;
 
@@ -53,6 +54,12 @@ static void test_format_commands() {
         len == 4+4+(3+2)+4+(3+2)+4+(0+2));
     free(cmd);
 
+    test("Format command with an empty string in between proper interpolations: ");
+    len = redisFormatCommand(&cmd,"SET %s %s","","foo");
+    test_cond(strncmp(cmd,"*3\r\n$3\r\nSET\r\n$0\r\n\r\n$3\r\nfoo\r\n",len) == 0 &&
+        len == 4+4+(3+2)+4+(0+2)+4+(3+2));
+    free(cmd);
+
     test("Format command with %%b string interpolation: ");
     len = redisFormatCommand(&cmd,"SET %b %b","foo",3,"b\0r",3);
     test_cond(strncmp(cmd,"*3\r\n$3\r\nSET\r\n$3\r\nfoo\r\n$3\r\nb\0r\r\n",len) == 0 &&
@@ -115,7 +122,7 @@ static void test_format_commands() {
     free(cmd);
 }
 
-static void test_blocking_connection() {
+static void test_blocking_connection(void) {
     redisContext *c;
     redisReply *reply;
     int major, minor;
@@ -246,13 +253,21 @@ static void test_blocking_connection() {
      * conditions, the error will be set to EOF. */
     assert(c->err == REDIS_ERR_EOF &&
         strcmp(c->errstr,"Server closed the connection") == 0);
+    redisFree(c);
 
-    /* Clean up context and reconnect again */
+    __connect(&c);
+    test("Returns I/O error on socket timeout: ");
+    struct timeval tv = { 0, 1000 };
+    assert(redisSetTimeout(c,tv) == REDIS_OK);
+    test_cond(redisGetReply(c,(void**)&reply) == REDIS_ERR &&
+        c->err == REDIS_ERR_IO && errno == EAGAIN);
     redisFree(c);
+
+    /* Context should be connected */
     __connect(&c);
 }
 
-static void test_reply_reader() {
+static void test_reply_reader(void) {
     void *reader;
     void *reply;
     char *err;
@@ -309,10 +324,19 @@ static void test_reply_reader() {
     ret = redisReplyReaderGetReply(reader,&reply);
     test_cond(ret == REDIS_OK && reply == (void*)REDIS_REPLY_STATUS);
     redisReplyReaderFree(reader);
+
+    test("Properly reset state after protocol error: ");
+    reader = redisReplyReaderCreate();
+    redisReplyReaderSetReplyObjectFunctions(reader,NULL);
+    redisReplyReaderFeed(reader,(char*)"x",1);
+    ret = redisReplyReaderGetReply(reader,&reply);
+    assert(ret == REDIS_ERR);
+    ret = redisReplyReaderGetReply(reader,&reply);
+    test_cond(ret == REDIS_OK && reply == NULL)
 }
 
-static void test_throughput() {
-    int i;
+static void test_throughput(void) {
+    int i, num;
     long long t1, t2;
     redisContext *c = blocking_context;
     redisReply **replies;
@@ -321,31 +345,60 @@ static void test_throughput() {
     for (i = 0; i < 500; i++)
         freeReplyObject(redisCommand(c,"LPUSH mylist foo"));
 
-    replies = malloc(sizeof(redisReply*)*1000);
+    num = 1000;
+    replies = malloc(sizeof(redisReply*)*num);
     t1 = usec();
-    for (i = 0; i < 1000; i++) {
+    for (i = 0; i < num; i++) {
         replies[i] = redisCommand(c,"PING");
         assert(replies[i] != NULL && replies[i]->type == REDIS_REPLY_STATUS);
     }
     t2 = usec();
-    for (i = 0; i < 1000; i++) freeReplyObject(replies[i]);
+    for (i = 0; i < num; i++) freeReplyObject(replies[i]);
     free(replies);
-    printf("\t(1000x PING: %.2fs)\n", (t2-t1)/1000000.0);
+    printf("\t(%dx PING: %.3fs)\n", num, (t2-t1)/1000000.0);
 
-    replies = malloc(sizeof(redisReply*)*1000);
+    replies = malloc(sizeof(redisReply*)*num);
     t1 = usec();
-    for (i = 0; i < 1000; i++) {
+    for (i = 0; i < num; i++) {
         replies[i] = redisCommand(c,"LRANGE mylist 0 499");
         assert(replies[i] != NULL && replies[i]->type == REDIS_REPLY_ARRAY);
         assert(replies[i] != NULL && replies[i]->elements == 500);
     }
     t2 = usec();
-    for (i = 0; i < 1000; i++) freeReplyObject(replies[i]);
+    for (i = 0; i < num; i++) freeReplyObject(replies[i]);
+    free(replies);
+    printf("\t(%dx LRANGE with 500 elements: %.3fs)\n", num, (t2-t1)/1000000.0);
+
+    num = 10000;
+    replies = malloc(sizeof(redisReply*)*num);
+    for (i = 0; i < num; i++)
+        redisAppendCommand(c,"PING");
+    t1 = usec();
+    for (i = 0; i < num; i++) {
+        assert(redisGetReply(c, (void*)&replies[i]) == REDIS_OK);
+        assert(replies[i] != NULL && replies[i]->type == REDIS_REPLY_STATUS);
+    }
+    t2 = usec();
+    for (i = 0; i < num; i++) freeReplyObject(replies[i]);
+    free(replies);
+    printf("\t(%dx PING (pipelined): %.3fs)\n", num, (t2-t1)/1000000.0);
+
+    replies = malloc(sizeof(redisReply*)*num);
+    for (i = 0; i < num; i++)
+        redisAppendCommand(c,"LRANGE mylist 0 499");
+    t1 = usec();
+    for (i = 0; i < num; i++) {
+        assert(redisGetReply(c, (void*)&replies[i]) == REDIS_OK);
+        assert(replies[i] != NULL && replies[i]->type == REDIS_REPLY_ARRAY);
+        assert(replies[i] != NULL && replies[i]->elements == 500);
+    }
+    t2 = usec();
+    for (i = 0; i < num; i++) freeReplyObject(replies[i]);
     free(replies);
-    printf("\t(1000x LRANGE with 500 elements: %.2fs)\n", (t2-t1)/1000000.0);
+    printf("\t(%dx LRANGE with 500 elements (pipelined): %.3fs)\n", num, (t2-t1)/1000000.0);
 }
 
-static void cleanup() {
+static void cleanup(void) {
     redisContext *c = blocking_context;
     redisReply *reply;
 