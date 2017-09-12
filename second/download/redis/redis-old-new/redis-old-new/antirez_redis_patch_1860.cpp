@@ -110,7 +110,8 @@ typedef struct redisContext {
 } redisContext;
 
 void freeReplyObject(void *reply);
-void *redisReplyReaderCreate(redisReplyObjectFunctions *fn);
+void *redisReplyReaderCreate();
+int redisReplyReaderSetReplyObjectFunctions(void *reader, redisReplyObjectFunctions *fn);
 void *redisReplyReaderGetObject(void *reader);
 char *redisReplyReaderGetError(void *reader);
 void redisReplyReaderFree(void *ptr);