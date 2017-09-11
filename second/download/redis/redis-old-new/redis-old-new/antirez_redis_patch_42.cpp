@@ -1,6 +1,8 @@
 /*
  * Copyright (c) 2009-2011, Salvatore Sanfilippo <antirez at gmail dot com>
- * Copyright (c) 2010-2011, Pieter Noordhuis <pcnoordhuis at gmail dot com>
+ * Copyright (c) 2010-2014, Pieter Noordhuis <pcnoordhuis at gmail dot com>
+ * Copyright (c) 2015, Matt Stancliff <matt at genges dot com>,
+ *                     Jan-Erik Rediger <janerik at fnordig dot com>
  *
  * All rights reserved.
  *
@@ -31,26 +33,16 @@
 
 #ifndef __HIREDIS_H
 #define __HIREDIS_H
-#include <stdio.h> /* for size_t */
+#include "read.h"
 #include <stdarg.h> /* for va_list */
 #include <sys/time.h> /* for struct timeval */
+#include <stdint.h> /* uintXX_t, etc */
+#include "sds.h" /* for sds */
 
 #define HIREDIS_MAJOR 0
-#define HIREDIS_MINOR 10
-#define HIREDIS_PATCH 1
-
-#define REDIS_ERR -1
-#define REDIS_OK 0
-
-/* When an error occurs, the err flag in a context is set to hold the type of
- * error that occured. REDIS_ERR_IO means there was an I/O error and you
- * should use the "errno" variable to find out what is wrong.
- * For other values, the "errstr" field will hold a description. */
-#define REDIS_ERR_IO 1 /* Error in read or write */
-#define REDIS_ERR_EOF 3 /* End of file */
-#define REDIS_ERR_PROTOCOL 4 /* Protocol error */
-#define REDIS_ERR_OOM 5 /* Out of memory */
-#define REDIS_ERR_OTHER 2 /* Everything else... */
+#define HIREDIS_MINOR 13
+#define HIREDIS_PATCH 3
+#define HIREDIS_SONAME 0.13
 
 /* Connection type can be blocking or non-blocking and is set in the
  * least significant bit of the flags field in redisContext. */
@@ -79,14 +71,38 @@
 /* Flag that is set when monitor mode is active */
 #define REDIS_MONITORING 0x40
 
-#define REDIS_REPLY_STRING 1
-#define REDIS_REPLY_ARRAY 2
-#define REDIS_REPLY_INTEGER 3
-#define REDIS_REPLY_NIL 4
-#define REDIS_REPLY_STATUS 5
-#define REDIS_REPLY_ERROR 6
-
-#define REDIS_READER_MAX_BUF (1024*16)  /* Default max unused reader buffer. */
+/* Flag that is set when we should set SO_REUSEADDR before calling bind() */
+#define REDIS_REUSEADDR 0x80
+
+#define REDIS_KEEPALIVE_INTERVAL 15 /* seconds */
+
+/* number of times we retry to connect in the case of EADDRNOTAVAIL and
+ * SO_REUSEADDR is being used. */
+#define REDIS_CONNECT_RETRIES  10
+
+/* strerror_r has two completely different prototypes and behaviors
+ * depending on system issues, so we need to operate on the error buffer
+ * differently depending on which strerror_r we're using. */
+#ifndef _GNU_SOURCE
+/* "regular" POSIX strerror_r that does the right thing. */
+#define __redis_strerror_r(errno, buf, len)                                    \
+    do {                                                                       \
+        strerror_r((errno), (buf), (len));                                     \
+    } while (0)
+#else
+/* "bad" GNU strerror_r we need to clean up after. */
+#define __redis_strerror_r(errno, buf, len)                                    \
+    do {                                                                       \
+        char *err_str = strerror_r((errno), (buf), (len));                     \
+        /* If return value _isn't_ the start of the buffer we passed in,       \
+         * then GNU strerror_r returned an internal static buffer and we       \
+         * need to copy the result into our private buffer. */                 \
+        if (err_str != (buf)) {                                                \
+            strncpy((buf), err_str, ((len) - 1));                              \
+            buf[(len)-1] = '\0';                                               \
+        }                                                                      \
+    } while (0)
+#endif
 
 #ifdef __cplusplus
 extern "C" {
@@ -96,61 +112,13 @@ extern "C" {
 typedef struct redisReply {
     int type; /* REDIS_REPLY_* */
     long long integer; /* The integer when type is REDIS_REPLY_INTEGER */
-    int len; /* Length of string */
+    size_t len; /* Length of string */
     char *str; /* Used for both REDIS_REPLY_ERROR and REDIS_REPLY_STRING */
     size_t elements; /* number of elements, for REDIS_REPLY_ARRAY */
     struct redisReply **element; /* elements vector for REDIS_REPLY_ARRAY */
 } redisReply;
 
-typedef struct redisReadTask {
-    int type;
-    int elements; /* number of elements in multibulk container */
-    int idx; /* index in parent (array) object */
-    void *obj; /* holds user-generated value for a read task */
-    struct redisReadTask *parent; /* parent task */
-    void *privdata; /* user-settable arbitrary field */
-} redisReadTask;
-
-typedef struct redisReplyObjectFunctions {
-    void *(*createString)(const redisReadTask*, char*, size_t);
-    void *(*createArray)(const redisReadTask*, int);
-    void *(*createInteger)(const redisReadTask*, long long);
-    void *(*createNil)(const redisReadTask*);
-    void (*freeObject)(void*);
-} redisReplyObjectFunctions;
-
-/* State for the protocol parser */
-typedef struct redisReader {
-    int err; /* Error flags, 0 when there is no error */
-    char errstr[128]; /* String representation of error when applicable */
-
-    char *buf; /* Read buffer */
-    size_t pos; /* Buffer cursor */
-    size_t len; /* Buffer length */
-    size_t maxbuf; /* Max length of unused buffer */
-
-    redisReadTask rstack[9];
-    int ridx; /* Index of current read task */
-    void *reply; /* Temporary reply pointer */
-
-    redisReplyObjectFunctions *fn;
-    void *privdata;
-} redisReader;
-
-/* Public API for the protocol parser. */
 redisReader *redisReaderCreate(void);
-void redisReaderFree(redisReader *r);
-int redisReaderFeed(redisReader *r, const char *buf, size_t len);
-int redisReaderGetReply(redisReader *r, void **reply);
-
-/* Backwards compatibility, can be removed on big version bump. */
-#define redisReplyReaderCreate redisReaderCreate
-#define redisReplyReaderFree redisReaderFree
-#define redisReplyReaderFeed redisReaderFeed
-#define redisReplyReaderGetReply redisReaderGetReply
-#define redisReplyReaderSetPrivdata(_r, _p) (int)(((redisReader*)(_r))->privdata = (_p))
-#define redisReplyReaderGetObject(_r) (((redisReader*)(_r))->reply)
-#define redisReplyReaderGetError(_r) (((redisReader*)(_r))->errstr)
 
 /* Function to free the reply objects hiredis returns by default. */
 void freeReplyObject(void *reply);
@@ -159,6 +127,14 @@ void freeReplyObject(void *reply);
 int redisvFormatCommand(char **target, const char *format, va_list ap);
 int redisFormatCommand(char **target, const char *format, ...);
 int redisFormatCommandArgv(char **target, int argc, const char **argv, const size_t *argvlen);
+int redisFormatSdsCommandArgv(sds *target, int argc, const char ** argv, const size_t *argvlen);
+void redisFreeCommand(char *cmd);
+void redisFreeSdsCommand(sds cmd);
+
+enum redisConnectionType {
+    REDIS_CONN_TCP,
+    REDIS_CONN_UNIX
+};
 
 /* Context for a connection to Redis */
 typedef struct redisContext {
@@ -168,16 +144,49 @@ typedef struct redisContext {
     int flags;
     char *obuf; /* Write buffer */
     redisReader *reader; /* Protocol reader */
+
+    enum redisConnectionType connection_type;
+    struct timeval *timeout;
+
+    struct {
+        char *host;
+        char *source_addr;
+        int port;
+    } tcp;
+
+    struct {
+        char *path;
+    } unix_sock;
+
 } redisContext;
 
 redisContext *redisConnect(const char *ip, int port);
-redisContext *redisConnectWithTimeout(const char *ip, int port, struct timeval tv);
+redisContext *redisConnectWithTimeout(const char *ip, int port, const struct timeval tv);
 redisContext *redisConnectNonBlock(const char *ip, int port);
+redisContext *redisConnectBindNonBlock(const char *ip, int port,
+                                       const char *source_addr);
+redisContext *redisConnectBindNonBlockWithReuse(const char *ip, int port,
+                                                const char *source_addr);
 redisContext *redisConnectUnix(const char *path);
-redisContext *redisConnectUnixWithTimeout(const char *path, struct timeval tv);
+redisContext *redisConnectUnixWithTimeout(const char *path, const struct timeval tv);
 redisContext *redisConnectUnixNonBlock(const char *path);
-int redisSetTimeout(redisContext *c, struct timeval tv);
+redisContext *redisConnectFd(int fd);
+
+/**
+ * Reconnect the given context using the saved information.
+ *
+ * This re-uses the exact same connect options as in the initial connection.
+ * host, ip (or path), timeout and bind address are reused,
+ * flags are used unmodified from the existing context.
+ *
+ * Returns REDIS_OK on successful connect or REDIS_ERR otherwise.
+ */
+int redisReconnect(redisContext *c);
+
+int redisSetTimeout(redisContext *c, const struct timeval tv);
+int redisEnableKeepAlive(redisContext *c);
 void redisFree(redisContext *c);
+int redisFreeKeepFd(redisContext *c);
 int redisBufferRead(redisContext *c);
 int redisBufferWrite(redisContext *c, int *done);
 
@@ -188,6 +197,10 @@ int redisBufferWrite(redisContext *c, int *done);
 int redisGetReply(redisContext *c, void **reply);
 int redisGetReplyFromReader(redisContext *c, void **reply);
 
+/* Write a formatted command to the output buffer. Use these functions in blocking mode
+ * to get a pipeline of commands. */
+int redisAppendFormattedCommand(redisContext *c, const char *cmd, size_t len);
+
 /* Write a command to the output buffer. Use these functions in blocking mode
  * to get a pipeline of commands. */
 int redisvAppendCommand(redisContext *c, const char *format, va_list ap);