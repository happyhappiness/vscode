@@ -33,6 +33,7 @@
 #define __HIREDIS_H
 #include <stdio.h> /* for size_t */
 #include <stdarg.h> /* for va_list */
+#include <sys/time.h> /* for struct timeval */
 
 #define HIREDIS_MAJOR 0
 #define HIREDIS_MINOR 9
@@ -64,6 +65,16 @@
  * should be terminated once all replies have been read. */
 #define REDIS_DISCONNECTING 0x4
 
+/* Flag specific to the async API which means that the context should be clean
+ * up as soon as possible. */
+#define REDIS_FREEING 0x8
+
+/* Flag that is set when an async callback is executed. */
+#define REDIS_IN_CALLBACK 0x10
+
+/* Flag that is set when the async context has one or more subscriptions. */
+#define REDIS_SUBSCRIBED 0x20
+
 #define REDIS_REPLY_STRING 1
 #define REDIS_REPLY_ARRAY 2
 #define REDIS_REPLY_INTEGER 3
@@ -118,13 +129,13 @@ typedef struct redisContext {
 } redisContext;
 
 void freeReplyObject(void *reply);
-void *redisReplyReaderCreate();
+void *redisReplyReaderCreate(void);
 int redisReplyReaderSetReplyObjectFunctions(void *reader, redisReplyObjectFunctions *fn);
 int redisReplyReaderSetPrivdata(void *reader, void *privdata);
 void *redisReplyReaderGetObject(void *reader);
 char *redisReplyReaderGetError(void *reader);
 void redisReplyReaderFree(void *ptr);
-void redisReplyReaderFeed(void *reader, char *buf, size_t len);
+void redisReplyReaderFeed(void *reader, const char *buf, size_t len);
 int redisReplyReaderGetReply(void *reader, void **reply);
 
 /* Functions to format a command according to the protocol. */
@@ -133,9 +144,12 @@ int redisFormatCommand(char **target, const char *format, ...);
 int redisFormatCommandArgv(char **target, int argc, const char **argv, const size_t *argvlen);
 
 redisContext *redisConnect(const char *ip, int port);
+redisContext *redisConnectWithTimeout(const char *ip, int port, struct timeval tv);
 redisContext *redisConnectNonBlock(const char *ip, int port);
 redisContext *redisConnectUnix(const char *path);
+redisContext *redisConnectUnixWithTimeout(const char *path, struct timeval tv);
 redisContext *redisConnectUnixNonBlock(const char *path);
+int redisSetTimeout(redisContext *c, struct timeval tv);
 int redisSetReplyObjectFunctions(redisContext *c, redisReplyObjectFunctions *fn);
 void redisFree(redisContext *c);
 int redisBufferRead(redisContext *c);