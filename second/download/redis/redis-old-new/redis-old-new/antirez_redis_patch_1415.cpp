@@ -1,6 +1,6 @@
 /*
- * Copyright (c) 2009-2010, Salvatore Sanfilippo <antirez at gmail dot com>
- * Copyright (c) 2010, Pieter Noordhuis <pcnoordhuis at gmail dot com>
+ * Copyright (c) 2009-2011, Salvatore Sanfilippo <antirez at gmail dot com>
+ * Copyright (c) 2010-2011, Pieter Noordhuis <pcnoordhuis at gmail dot com>
  *
  * All rights reserved.
  *
@@ -36,8 +36,8 @@
 #include <sys/time.h> /* for struct timeval */
 
 #define HIREDIS_MAJOR 0
-#define HIREDIS_MINOR 9
-#define HIREDIS_PATCH 2
+#define HIREDIS_MINOR 10
+#define HIREDIS_PATCH 1
 
 #define REDIS_ERR -1
 #define REDIS_OK 0
@@ -46,10 +46,11 @@
  * error that occured. REDIS_ERR_IO means there was an I/O error and you
  * should use the "errno" variable to find out what is wrong.
  * For other values, the "errstr" field will hold a description. */
-#define REDIS_ERR_IO 1 /* error in read or write */
-#define REDIS_ERR_EOF 3 /* eof */
-#define REDIS_ERR_PROTOCOL 4 /* protocol error */
-#define REDIS_ERR_OTHER 2 /* something else */
+#define REDIS_ERR_IO 1 /* Error in read or write */
+#define REDIS_ERR_EOF 3 /* End of file */
+#define REDIS_ERR_PROTOCOL 4 /* Protocol error */
+#define REDIS_ERR_OOM 5 /* Out of memory */
+#define REDIS_ERR_OTHER 2 /* Everything else... */
 
 /* Connection type can be blocking or non-blocking and is set in the
  * least significant bit of the flags field in redisContext. */
@@ -113,44 +114,63 @@ typedef struct redisReplyObjectFunctions {
     void (*freeObject)(void*);
 } redisReplyObjectFunctions;
 
-struct redisContext; /* need forward declaration of redisContext */
-
-/* Context for a connection to Redis */
-typedef struct redisContext {
-    int fd;
-    int flags;
-    char *obuf; /* Write buffer */
+/* State for the protocol parser */
+typedef struct redisReader {
     int err; /* Error flags, 0 when there is no error */
-    char *errstr; /* String representation of error when applicable */
+    char errstr[128]; /* String representation of error when applicable */
 
-    /* Function set for reply buildup and reply reader */
-    redisReplyObjectFunctions *fn;
-    void *reader;
-} redisContext;
+    char *buf; /* Read buffer */
+    size_t pos; /* Buffer cursor */
+    size_t len; /* Buffer length */
+
+    redisReadTask rstack[4];
+    int ridx; /* Index of current read task */
+    void *reply; /* Temporary reply pointer */
 
+    redisReplyObjectFunctions *fn;
+    void *privdata;
+} redisReader;
+
+/* Public API for the protocol parser. */
+redisReader *redisReaderCreate(void);
+void redisReaderFree(redisReader *r);
+int redisReaderFeed(redisReader *r, const char *buf, size_t len);
+int redisReaderGetReply(redisReader *r, void **reply);
+
+/* Backwards compatibility, can be removed on big version bump. */
+#define redisReplyReaderCreate redisReaderCreate
+#define redisReplyReaderFree redisReaderFree
+#define redisReplyReaderFeed redisReaderFeed
+#define redisReplyReaderGetReply redisReaderGetReply
+#define redisReplyReaderSetPrivdata(_r, _p) (int)(((redisReader*)(_r))->privdata = (_p))
+#define redisReplyReaderGetObject(_r) (((redisReader*)(_r))->reply)
+#define redisReplyReaderGetError(_r) (((redisReader*)(_r))->errstr)
+
+/* Function to free the reply objects hiredis returns by default. */
 void freeReplyObject(void *reply);
-void *redisReplyReaderCreate(void);
-int redisReplyReaderSetReplyObjectFunctions(void *reader, redisReplyObjectFunctions *fn);
-int redisReplyReaderSetPrivdata(void *reader, void *privdata);
-void *redisReplyReaderGetObject(void *reader);
-char *redisReplyReaderGetError(void *reader);
-void redisReplyReaderFree(void *ptr);
-void redisReplyReaderFeed(void *reader, const char *buf, size_t len);
-int redisReplyReaderGetReply(void *reader, void **reply);
 
 /* Functions to format a command according to the protocol. */
 int redisvFormatCommand(char **target, const char *format, va_list ap);
 int redisFormatCommand(char **target, const char *format, ...);
 int redisFormatCommandArgv(char **target, int argc, const char **argv, const size_t *argvlen);
 
+/* Context for a connection to Redis */
+typedef struct redisContext {
+    int err; /* Error flags, 0 when there is no error */
+    char errstr[128]; /* String representation of error when applicable */
+    int fd;
+    int flags;
+    char *obuf; /* Write buffer */
+    redisReader *reader; /* Protocol reader */
+} redisContext;
+
 redisContext *redisConnect(const char *ip, int port);
 redisContext *redisConnectWithTimeout(const char *ip, int port, struct timeval tv);
 redisContext *redisConnectNonBlock(const char *ip, int port);
 redisContext *redisConnectUnix(const char *path);
 redisContext *redisConnectUnixWithTimeout(const char *path, struct timeval tv);
 redisContext *redisConnectUnixNonBlock(const char *path);
 int redisSetTimeout(redisContext *c, struct timeval tv);
-int redisSetReplyObjectFunctions(redisContext *c, redisReplyObjectFunctions *fn);
 void redisFree(redisContext *c);
 int redisBufferRead(redisContext *c);
 int redisBufferWrite(redisContext *c, int *done);
@@ -164,9 +184,9 @@ int redisGetReplyFromReader(redisContext *c, void **reply);
 
 /* Write a command to the output buffer. Use these functions in blocking mode
  * to get a pipeline of commands. */
-void redisvAppendCommand(redisContext *c, const char *format, va_list ap);
-void redisAppendCommand(redisContext *c, const char *format, ...);
-void redisAppendCommandArgv(redisContext *c, int argc, const char **argv, const size_t *argvlen);
+int redisvAppendCommand(redisContext *c, const char *format, va_list ap);
+int redisAppendCommand(redisContext *c, const char *format, ...);
+int redisAppendCommandArgv(redisContext *c, int argc, const char **argv, const size_t *argvlen);
 
 /* Issue a command to Redis. In a blocking context, it is identical to calling
  * redisAppendCommand, followed by redisGetReply. The function will return