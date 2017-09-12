@@ -1,5 +1,7 @@
 /*
  * Copyright (c) 2009-2010, Salvatore Sanfilippo <antirez at gmail dot com>
+ * Copyright (c) 2010, Pieter Noordhuis <pcnoordhuis at gmail dot com>
+ *
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
@@ -34,7 +36,7 @@
 
 #define HIREDIS_MAJOR 0
 #define HIREDIS_MINOR 9
-#define HIREDIS_PATCH 0
+#define HIREDIS_PATCH 2
 
 #define REDIS_ERR -1
 #define REDIS_OK 0
@@ -62,12 +64,16 @@
  * should be terminated once all replies have been read. */
 #define REDIS_DISCONNECTING 0x4
 
-#define REDIS_REPLY_ERROR 0
 #define REDIS_REPLY_STRING 1
 #define REDIS_REPLY_ARRAY 2
 #define REDIS_REPLY_INTEGER 3
 #define REDIS_REPLY_NIL 4
 #define REDIS_REPLY_STATUS 5
+#define REDIS_REPLY_ERROR 6
+
+#ifdef __cplusplus
+extern "C" {
+#endif
 
 /* This is the reply object returned by redisCommand() */
 typedef struct redisReply {
@@ -82,8 +88,10 @@ typedef struct redisReply {
 typedef struct redisReadTask {
     int type;
     int elements; /* number of elements in multibulk container */
-    void *parent; /* optional pointer to parent object */
     int idx; /* index in parent (array) object */
+    void *obj; /* holds user-generated value for a read task */
+    struct redisReadTask *parent; /* parent task */
+    void *privdata; /* user-settable arbitrary field */
 } redisReadTask;
 
 typedef struct redisReplyObjectFunctions {
@@ -112,6 +120,7 @@ typedef struct redisContext {
 void freeReplyObject(void *reply);
 void *redisReplyReaderCreate();
 int redisReplyReaderSetReplyObjectFunctions(void *reader, redisReplyObjectFunctions *fn);
+int redisReplyReaderSetPrivdata(void *reader, void *privdata);
 void *redisReplyReaderGetObject(void *reader);
 char *redisReplyReaderGetError(void *reader);
 void redisReplyReaderFree(void *ptr);
@@ -154,4 +163,8 @@ void *redisvCommand(redisContext *c, const char *format, va_list ap);
 void *redisCommand(redisContext *c, const char *format, ...);
 void *redisCommandArgv(redisContext *c, int argc, const char **argv, const size_t *argvlen);
 
+#ifdef __cplusplus
+}
+#endif
+
 #endif