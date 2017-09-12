@@ -115,7 +115,7 @@ int redisReplyReaderSetReplyObjectFunctions(void *reader, redisReplyObjectFuncti
 void *redisReplyReaderGetObject(void *reader);
 char *redisReplyReaderGetError(void *reader);
 void redisReplyReaderFree(void *ptr);
-void redisReplyReaderFeed(void *reader, char *buf, int len);
+void redisReplyReaderFeed(void *reader, char *buf, size_t len);
 int redisReplyReaderGetReply(void *reader, void **reply);
 
 /* Functions to format a command according to the protocol. */