@@ -1,6 +1,6 @@
 /*
- * Copyright (c) 2009-2010, Salvatore Sanfilippo <antirez at gmail dot com>
- * Copyright (c) 2010, Pieter Noordhuis <pcnoordhuis at gmail dot com>
+ * Copyright (c) 2009-2011, Salvatore Sanfilippo <antirez at gmail dot com>
+ * Copyright (c) 2010-2011, Pieter Noordhuis <pcnoordhuis at gmail dot com>
  *
  * All rights reserved.
  *
@@ -29,14 +29,33 @@
  * POSSIBILITY OF SUCH DAMAGE.
  */
 
+#include "fmacros.h"
+#include <stdlib.h>
 #include <string.h>
 #include <strings.h>
 #include <assert.h>
 #include <ctype.h>
+#include <errno.h>
 #include "async.h"
+#include "net.h"
 #include "dict.c"
 #include "sds.h"
-#include "util.h"
+
+#define _EL_ADD_READ(ctx) do { \
+        if ((ctx)->ev.addRead) (ctx)->ev.addRead((ctx)->ev.data); \
+    } while(0)
+#define _EL_DEL_READ(ctx) do { \
+        if ((ctx)->ev.delRead) (ctx)->ev.delRead((ctx)->ev.data); \
+    } while(0)
+#define _EL_ADD_WRITE(ctx) do { \
+        if ((ctx)->ev.addWrite) (ctx)->ev.addWrite((ctx)->ev.data); \
+    } while(0)
+#define _EL_DEL_WRITE(ctx) do { \
+        if ((ctx)->ev.delWrite) (ctx)->ev.delWrite((ctx)->ev.data); \
+    } while(0)
+#define _EL_CLEANUP(ctx) do { \
+        if ((ctx)->ev.cleanup) (ctx)->ev.cleanup((ctx)->ev.data); \
+    } while(0);
 
 /* Forward declaration of function in hiredis.c */
 void __redisAppendCommand(redisContext *c, char *cmd, size_t len);
@@ -136,19 +155,14 @@ redisAsyncContext *redisAsyncConnectUnix(const char *path) {
     return ac;
 }
 
-int redisAsyncSetReplyObjectFunctions(redisAsyncContext *ac, redisReplyObjectFunctions *fn) {
-    redisContext *c = &(ac->c);
-    return redisSetReplyObjectFunctions(c,fn);
-}
-
 int redisAsyncSetConnectCallback(redisAsyncContext *ac, redisConnectCallback *fn) {
     if (ac->onConnect == NULL) {
         ac->onConnect = fn;
 
         /* The common way to detect an established connection is to wait for
          * the first write event to be fired. This assumes the related event
          * library functions are already set. */
-        if (ac->ev.addWrite) ac->ev.addWrite(ac->ev.data);
+        _EL_ADD_WRITE(ac);
         return REDIS_OK;
     }
     return REDIS_ERR;
@@ -168,7 +182,6 @@ static int __redisPushCallback(redisCallbackList *list, redisCallback *source) {
 
     /* Copy callback from stack to heap */
     cb = malloc(sizeof(*cb));
-    if (!cb) redisOOM();
     if (source != NULL) {
         memcpy(cb,source,sizeof(*cb));
         cb->next = NULL;
@@ -237,7 +250,7 @@ static void __redisAsyncFree(redisAsyncContext *ac) {
     dictRelease(ac->sub.patterns);
 
     /* Signal event lib to clean up */
-    if (ac->ev.cleanup) ac->ev.cleanup(ac->ev.data);
+    _EL_CLEANUP(ac);
 
     /* Execute disconnect callback. When redisAsyncFree() initiated destroying
      * this context, the status will always be REDIS_OK. */
@@ -368,14 +381,27 @@ void redisProcessCallbacks(redisAsyncContext *ac) {
         /* Even if the context is subscribed, pending regular callbacks will
          * get a reply before pub/sub messages arrive. */
         if (__redisShiftCallback(&ac->replies,&cb) != REDIS_OK) {
-            /* No more regular callbacks, the context *must* be subscribed. */
+            /* A spontaneous reply in a not-subscribed context can only be the
+             * error reply that is sent when a new connection exceeds the
+             * maximum number of allowed connections on the server side. This
+             * is seen as an error instead of a regular reply because the
+             * server closes the connection after sending it. To prevent the
+             * error from being overwritten by an EOF error the connection is
+             * closed here. See issue #43. */
+            if ( !(c->flags & REDIS_SUBSCRIBED) && ((redisReply*)reply)->type == REDIS_REPLY_ERROR ) {
+                c->err = REDIS_ERR_OTHER;
+                snprintf(c->errstr,sizeof(c->errstr),"%s",((redisReply*)reply)->str);
+                __redisAsyncDisconnect(ac);
+                return;
+            }
+            /* No more regular callbacks and no errors, the context *must* be subscribed. */
             assert(c->flags & REDIS_SUBSCRIBED);
             __redisGetSubscribeCallback(ac,reply,&cb);
         }
 
         if (cb.fn != NULL) {
             __redisRunCallback(ac,&cb,reply);
-            c->fn->freeObject(reply);
+            c->reader->fn->freeObject(reply);
 
             /* Proceed with free'ing when redisAsyncFree() was called. */
             if (c->flags & REDIS_FREEING) {
@@ -387,7 +413,7 @@ void redisProcessCallbacks(redisAsyncContext *ac) {
              * or there were no callbacks to begin with. Either way, don't
              * abort with an error, but simply ignore it because the client
              * doesn't know what the server will spit out over the wire. */
-            c->fn->freeObject(reply);
+            c->reader->fn->freeObject(reply);
         }
     }
 
@@ -396,17 +422,48 @@ void redisProcessCallbacks(redisAsyncContext *ac) {
         __redisAsyncDisconnect(ac);
 }
 
+/* Internal helper function to detect socket status the first time a read or
+ * write event fires. When connecting was not succesful, the connect callback
+ * is called with a REDIS_ERR status and the context is free'd. */
+static int __redisAsyncHandleConnect(redisAsyncContext *ac) {
+    redisContext *c = &(ac->c);
+
+    if (redisCheckSocketError(c,c->fd) == REDIS_ERR) {
+        /* Try again later when connect(2) is still in progress. */
+        if (errno == EINPROGRESS)
+            return REDIS_OK;
+
+        if (ac->onConnect) ac->onConnect(ac,REDIS_ERR);
+        __redisAsyncDisconnect(ac);
+        return REDIS_ERR;
+    }
+
+    /* Mark context as connected. */
+    c->flags |= REDIS_CONNECTED;
+    if (ac->onConnect) ac->onConnect(ac,REDIS_OK);
+    return REDIS_OK;
+}
+
 /* This function should be called when the socket is readable.
  * It processes all replies that can be read and executes their callbacks.
  */
 void redisAsyncHandleRead(redisAsyncContext *ac) {
     redisContext *c = &(ac->c);
 
+    if (!(c->flags & REDIS_CONNECTED)) {
+        /* Abort connect was not successful. */
+        if (__redisAsyncHandleConnect(ac) != REDIS_OK)
+            return;
+        /* Try again later when the context is still not connected. */
+        if (!(c->flags & REDIS_CONNECTED))
+            return;
+    }
+
     if (redisBufferRead(c) == REDIS_ERR) {
         __redisAsyncDisconnect(ac);
     } else {
         /* Always re-schedule reads */
-        if (ac->ev.addRead) ac->ev.addRead(ac->ev.data);
+        _EL_ADD_READ(ac);
         redisProcessCallbacks(ac);
     }
 }
@@ -415,24 +472,26 @@ void redisAsyncHandleWrite(redisAsyncContext *ac) {
     redisContext *c = &(ac->c);
     int done = 0;
 
+    if (!(c->flags & REDIS_CONNECTED)) {
+        /* Abort connect was not successful. */
+        if (__redisAsyncHandleConnect(ac) != REDIS_OK)
+            return;
+        /* Try again later when the context is still not connected. */
+        if (!(c->flags & REDIS_CONNECTED))
+            return;
+    }
+
     if (redisBufferWrite(c,&done) == REDIS_ERR) {
         __redisAsyncDisconnect(ac);
     } else {
         /* Continue writing when not done, stop writing otherwise */
-        if (!done) {
-            if (ac->ev.addWrite) ac->ev.addWrite(ac->ev.data);
-        } else {
-            if (ac->ev.delWrite) ac->ev.delWrite(ac->ev.data);
-        }
+        if (!done)
+            _EL_ADD_WRITE(ac);
+        else
+            _EL_DEL_WRITE(ac);
 
         /* Always schedule reads after writes */
-        if (ac->ev.addRead) ac->ev.addRead(ac->ev.data);
-
-        /* Fire onConnect when this is the first write event. */
-        if (!(c->flags & REDIS_CONNECTED)) {
-            c->flags |= REDIS_CONNECTED;
-            if (ac->onConnect) ac->onConnect(ac);
-        }
+        _EL_ADD_READ(ac);
     }
 }
 
@@ -510,7 +569,7 @@ static int __redisAsyncCommand(redisAsyncContext *ac, redisCallbackFn *fn, void
     __redisAppendCommand(c,cmd,len);
 
     /* Always schedule a write when the write buffer is non-empty */
-    if (ac->ev.addWrite) ac->ev.addWrite(ac->ev.data);
+    _EL_ADD_WRITE(ac);
 
     return REDIS_OK;
 }