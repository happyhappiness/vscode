@@ -186,11 +186,12 @@ static void test_blocking_connection() {
 
 static void test_reply_reader() {
     void *reader;
+    void *reply;
     char *err;
     int ret;
 
     test("Error handling in reply parser: ");
-    reader = redisReplyReaderCreate(NULL);
+    reader = redisReplyReaderCreate();
     redisReplyReaderFeed(reader,(char*)"@foo\r\n",6);
     ret = redisReplyReaderGetReply(reader,NULL);
     err = redisReplyReaderGetError(reader);
@@ -201,7 +202,7 @@ static void test_reply_reader() {
     /* when the reply already contains multiple items, they must be free'd
      * on an error. valgrind will bark when this doesn't happen. */
     test("Memory cleanup in reply parser: ");
-    reader = redisReplyReaderCreate(NULL);
+    reader = redisReplyReaderCreate();
     redisReplyReaderFeed(reader,(char*)"*2\r\n",4);
     redisReplyReaderFeed(reader,(char*)"$5\r\nhello\r\n",11);
     redisReplyReaderFeed(reader,(char*)"@foo\r\n",6);
@@ -210,6 +211,14 @@ static void test_reply_reader() {
     test_cond(ret == REDIS_ERR &&
               strcasecmp(err,"protocol error, got \"@\" as reply type byte") == 0);
     redisReplyReaderFree(reader);
+
+    test("Works with NULL functions for reply: ");
+    reader = redisReplyReaderCreate();
+    redisReplyReaderSetReplyObjectFunctions(reader,NULL);
+    redisReplyReaderFeed(reader,(char*)"+OK\r\n",5);
+    ret = redisReplyReaderGetReply(reader,&reply);
+    test_cond(ret == REDIS_OK && reply == (void*)REDIS_REPLY_STATUS);
+    redisReplyReaderFree(reader);
 }
 
 static void test_throughput() {