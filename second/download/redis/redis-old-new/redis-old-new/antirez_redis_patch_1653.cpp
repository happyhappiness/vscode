@@ -30,14 +30,58 @@
  */
 
 #include <string.h>
+#include <strings.h>
 #include <assert.h>
+#include <ctype.h>
 #include "async.h"
+#include "dict.c"
 #include "sds.h"
 #include "util.h"
 
 /* Forward declaration of function in hiredis.c */
 void __redisAppendCommand(redisContext *c, char *cmd, size_t len);
 
+/* Functions managing dictionary of callbacks for pub/sub. */
+static unsigned int callbackHash(const void *key) {
+    return dictGenHashFunction((unsigned char*)key,sdslen((char*)key));
+}
+
+static void *callbackValDup(void *privdata, const void *src) {
+    ((void) privdata);
+    redisCallback *dup = malloc(sizeof(*dup));
+    memcpy(dup,src,sizeof(*dup));
+    return dup;
+}
+
+static int callbackKeyCompare(void *privdata, const void *key1, const void *key2) {
+    int l1, l2;
+    ((void) privdata);
+
+    l1 = sdslen((sds)key1);
+    l2 = sdslen((sds)key2);
+    if (l1 != l2) return 0;
+    return memcmp(key1,key2,l1) == 0;
+}
+
+static void callbackKeyDestructor(void *privdata, void *key) {
+    ((void) privdata);
+    sdsfree((sds)key);
+}
+
+static void callbackValDestructor(void *privdata, void *val) {
+    ((void) privdata);
+    free(val);
+}
+
+static dictType callbackDict = {
+    callbackHash,
+    NULL,
+    callbackValDup,
+    callbackKeyCompare,
+    callbackKeyDestructor,
+    callbackValDestructor
+};
+
 static redisAsyncContext *redisAsyncInitialize(redisContext *c) {
     redisAsyncContext *ac = realloc(c,sizeof(redisAsyncContext));
     c = &(ac->c);
@@ -50,19 +94,23 @@ static redisAsyncContext *redisAsyncInitialize(redisContext *c) {
     ac->err = 0;
     ac->errstr = NULL;
     ac->data = NULL;
-    ac->_adapter_data = NULL;
 
-    ac->evAddRead = NULL;
-    ac->evDelRead = NULL;
-    ac->evAddWrite = NULL;
-    ac->evDelWrite = NULL;
-    ac->evCleanup = NULL;
+    ac->ev.data = NULL;
+    ac->ev.addRead = NULL;
+    ac->ev.delRead = NULL;
+    ac->ev.addWrite = NULL;
+    ac->ev.delWrite = NULL;
+    ac->ev.cleanup = NULL;
 
     ac->onConnect = NULL;
     ac->onDisconnect = NULL;
 
     ac->replies.head = NULL;
     ac->replies.tail = NULL;
+    ac->sub.invalid.head = NULL;
+    ac->sub.invalid.tail = NULL;
+    ac->sub.channels = dictCreate(&callbackDict,NULL);
+    ac->sub.patterns = dictCreate(&callbackDict,NULL);
     return ac;
 }
 
@@ -96,6 +144,11 @@ int redisAsyncSetReplyObjectFunctions(redisAsyncContext *ac, redisReplyObjectFun
 int redisAsyncSetConnectCallback(redisAsyncContext *ac, redisConnectCallback *fn) {
     if (ac->onConnect == NULL) {
         ac->onConnect = fn;
+
+        /* The common way to detect an established connection is to wait for
+         * the first write event to be fired. This assumes the related event
+         * library functions are already set. */
+        if (ac->ev.addWrite) ac->ev.addWrite(ac->ev.data);
         return REDIS_OK;
     }
     return REDIS_ERR;
@@ -114,11 +167,11 @@ static int __redisPushCallback(redisCallbackList *list, redisCallback *source) {
     redisCallback *cb;
 
     /* Copy callback from stack to heap */
-    cb = calloc(1,sizeof(*cb));
+    cb = malloc(sizeof(*cb));
     if (!cb) redisOOM();
     if (source != NULL) {
-        cb->fn = source->fn;
-        cb->privdata = source->privdata;
+        memcpy(cb,source,sizeof(*cb));
+        cb->next = NULL;
     }
 
     /* Store callback in list */
@@ -146,51 +199,150 @@ static int __redisShiftCallback(redisCallbackList *list, redisCallback *target)
     return REDIS_ERR;
 }
 
-/* Tries to do a clean disconnect from Redis, meaning it stops new commands
- * from being issued, but tries to flush the output buffer and execute
- * callbacks for all remaining replies.
- *
- * This functions is generally called from within a callback, so the
- * processCallbacks function will pick up the flag when there are no
- * more replies. */
-void redisAsyncDisconnect(redisAsyncContext *ac) {
+static void __redisRunCallback(redisAsyncContext *ac, redisCallback *cb, redisReply *reply) {
     redisContext *c = &(ac->c);
-    c->flags |= REDIS_DISCONNECTING;
+    if (cb->fn != NULL) {
+        c->flags |= REDIS_IN_CALLBACK;
+        cb->fn(ac,reply,cb->privdata);
+        c->flags &= ~REDIS_IN_CALLBACK;
+    }
+}
+
+/* Helper function to free the context. */
+static void __redisAsyncFree(redisAsyncContext *ac) {
+    redisContext *c = &(ac->c);
+    redisCallback cb;
+    dictIterator *it;
+    dictEntry *de;
+
+    /* Execute pending callbacks with NULL reply. */
+    while (__redisShiftCallback(&ac->replies,&cb) == REDIS_OK)
+        __redisRunCallback(ac,&cb,NULL);
+
+    /* Execute callbacks for invalid commands */
+    while (__redisShiftCallback(&ac->sub.invalid,&cb) == REDIS_OK)
+        __redisRunCallback(ac,&cb,NULL);
+
+    /* Run subscription callbacks callbacks with NULL reply */
+    it = dictGetIterator(ac->sub.channels);
+    while ((de = dictNext(it)) != NULL)
+        __redisRunCallback(ac,dictGetEntryVal(de),NULL);
+    dictReleaseIterator(it);
+    dictRelease(ac->sub.channels);
+
+    it = dictGetIterator(ac->sub.patterns);
+    while ((de = dictNext(it)) != NULL)
+        __redisRunCallback(ac,dictGetEntryVal(de),NULL);
+    dictReleaseIterator(it);
+    dictRelease(ac->sub.patterns);
+
+    /* Signal event lib to clean up */
+    if (ac->ev.cleanup) ac->ev.cleanup(ac->ev.data);
+
+    /* Execute disconnect callback. When redisAsyncFree() initiated destroying
+     * this context, the status will always be REDIS_OK. */
+    if (ac->onDisconnect && (c->flags & REDIS_CONNECTED)) {
+        if (c->flags & REDIS_FREEING) {
+            ac->onDisconnect(ac,REDIS_OK);
+        } else {
+            ac->onDisconnect(ac,(ac->err == 0) ? REDIS_OK : REDIS_ERR);
+        }
+    }
+
+    /* Cleanup self */
+    redisFree(c);
+}
+
+/* Free the async context. When this function is called from a callback,
+ * control needs to be returned to redisProcessCallbacks() before actual
+ * free'ing. To do so, a flag is set on the context which is picked up by
+ * redisProcessCallbacks(). Otherwise, the context is immediately free'd. */
+void redisAsyncFree(redisAsyncContext *ac) {
+    redisContext *c = &(ac->c);
+    c->flags |= REDIS_FREEING;
+    if (!(c->flags & REDIS_IN_CALLBACK))
+        __redisAsyncFree(ac);
 }
 
 /* Helper function to make the disconnect happen and clean up. */
 static void __redisAsyncDisconnect(redisAsyncContext *ac) {
     redisContext *c = &(ac->c);
-    redisCallback cb;
-    int status;
 
     /* Make sure error is accessible if there is any */
     __redisAsyncCopyError(ac);
-    status = (ac->err == 0) ? REDIS_OK : REDIS_ERR;
 
-    if (status == REDIS_OK) {
-        /* When the connection is cleanly disconnected, there should not
-         * be pending callbacks. */
+    if (ac->err == 0) {
+        /* For clean disconnects, there should be no pending callbacks. */
         assert(__redisShiftCallback(&ac->replies,NULL) == REDIS_ERR);
     } else {
-        /* Callbacks should not be able to issue new commands. */
+        /* Disconnection is caused by an error, make sure that pending
+         * callbacks cannot call new commands. */
         c->flags |= REDIS_DISCONNECTING;
-
-        /* Execute pending callbacks with NULL reply. */
-        while (__redisShiftCallback(&ac->replies,&cb) == REDIS_OK) {
-            if (cb.fn != NULL)
-                cb.fn(ac,NULL,cb.privdata);
-        }
     }
 
-    /* Signal event lib to clean up */
-    if (ac->evCleanup) ac->evCleanup(ac->_adapter_data);
+    /* For non-clean disconnects, __redisAsyncFree() will execute pending
+     * callbacks with a NULL-reply. */
+    __redisAsyncFree(ac);
+}
 
-    /* Execute callback with proper status */
-    if (ac->onDisconnect) ac->onDisconnect(ac,status);
+/* Tries to do a clean disconnect from Redis, meaning it stops new commands
+ * from being issued, but tries to flush the output buffer and execute
+ * callbacks for all remaining replies. When this function is called from a
+ * callback, there might be more replies and we can safely defer disconnecting
+ * to redisProcessCallbacks(). Otherwise, we can only disconnect immediately
+ * when there are no pending callbacks. */
+void redisAsyncDisconnect(redisAsyncContext *ac) {
+    redisContext *c = &(ac->c);
+    c->flags |= REDIS_DISCONNECTING;
+    if (!(c->flags & REDIS_IN_CALLBACK) && ac->replies.head == NULL)
+        __redisAsyncDisconnect(ac);
+}
 
-    /* Cleanup self */
-    redisFree(c);
+static int __redisGetSubscribeCallback(redisAsyncContext *ac, redisReply *reply, redisCallback *dstcb) {
+    redisContext *c = &(ac->c);
+    dict *callbacks;
+    dictEntry *de;
+    int pvariant;
+    char *stype;
+    sds sname;
+
+    /* Custom reply functions are not supported for pub/sub. This will fail
+     * very hard when they are used... */
+    if (reply->type == REDIS_REPLY_ARRAY) {
+        assert(reply->elements >= 2);
+        assert(reply->element[0]->type == REDIS_REPLY_STRING);
+        stype = reply->element[0]->str;
+        pvariant = (tolower(stype[0]) == 'p') ? 1 : 0;
+
+        if (pvariant)
+            callbacks = ac->sub.patterns;
+        else
+            callbacks = ac->sub.channels;
+
+        /* Locate the right callback */
+        assert(reply->element[1]->type == REDIS_REPLY_STRING);
+        sname = sdsnewlen(reply->element[1]->str,reply->element[1]->len);
+        de = dictFind(callbacks,sname);
+        if (de != NULL) {
+            memcpy(dstcb,dictGetEntryVal(de),sizeof(*dstcb));
+
+            /* If this is an unsubscribe message, remove it. */
+            if (strcasecmp(stype+pvariant,"unsubscribe") == 0) {
+                dictDelete(callbacks,sname);
+
+                /* If this was the last unsubscribe message, revert to
+                 * non-subscribe mode. */
+                assert(reply->element[2]->type == REDIS_REPLY_INTEGER);
+                if (reply->element[2]->integer == 0)
+                    c->flags &= ~REDIS_SUBSCRIBED;
+            }
+        }
+        sdsfree(sname);
+    } else {
+        /* Shift callback for invalid commands. */
+        __redisShiftCallback(&ac->sub.invalid,dstcb);
+    }
+    return REDIS_OK;
 }
 
 void redisProcessCallbacks(redisAsyncContext *ac) {
@@ -213,11 +365,28 @@ void redisProcessCallbacks(redisAsyncContext *ac) {
             break;
         }
 
-        /* Shift callback and execute it */
-        assert(__redisShiftCallback(&ac->replies,&cb) == REDIS_OK);
+        /* Even if the context is subscribed, pending regular callbacks will
+         * get a reply before pub/sub messages arrive. */
+        if (__redisShiftCallback(&ac->replies,&cb) != REDIS_OK) {
+            /* No more regular callbacks, the context *must* be subscribed. */
+            assert(c->flags & REDIS_SUBSCRIBED);
+            __redisGetSubscribeCallback(ac,reply,&cb);
+        }
+
         if (cb.fn != NULL) {
-            cb.fn(ac,reply,cb.privdata);
+            __redisRunCallback(ac,&cb,reply);
+            c->fn->freeObject(reply);
+
+            /* Proceed with free'ing when redisAsyncFree() was called. */
+            if (c->flags & REDIS_FREEING) {
+                __redisAsyncFree(ac);
+                return;
+            }
         } else {
+            /* No callback for this reply. This can either be a NULL callback,
+             * or there were no callbacks to begin with. Either way, don't
+             * abort with an error, but simply ignore it because the client
+             * doesn't know what the server will spit out over the wire. */
             c->fn->freeObject(reply);
         }
     }
@@ -237,7 +406,7 @@ void redisAsyncHandleRead(redisAsyncContext *ac) {
         __redisAsyncDisconnect(ac);
     } else {
         /* Always re-schedule reads */
-        if (ac->evAddRead) ac->evAddRead(ac->_adapter_data);
+        if (ac->ev.addRead) ac->ev.addRead(ac->ev.data);
         redisProcessCallbacks(ac);
     }
 }
@@ -251,13 +420,13 @@ void redisAsyncHandleWrite(redisAsyncContext *ac) {
     } else {
         /* Continue writing when not done, stop writing otherwise */
         if (!done) {
-            if (ac->evAddWrite) ac->evAddWrite(ac->_adapter_data);
+            if (ac->ev.addWrite) ac->ev.addWrite(ac->ev.data);
         } else {
-            if (ac->evDelWrite) ac->evDelWrite(ac->_adapter_data);
+            if (ac->ev.delWrite) ac->ev.delWrite(ac->ev.data);
         }
 
         /* Always schedule reads after writes */
-        if (ac->evAddRead) ac->evAddRead(ac->_adapter_data);
+        if (ac->ev.addRead) ac->ev.addRead(ac->ev.data);
 
         /* Fire onConnect when this is the first write event. */
         if (!(c->flags & REDIS_CONNECTED)) {
@@ -267,26 +436,81 @@ void redisAsyncHandleWrite(redisAsyncContext *ac) {
     }
 }
 
-/* Helper function for the redisAsyncCommand* family of functions.
- *
- * Write a formatted command to the output buffer and register the provided
- * callback function with the context.
- */
+/* Sets a pointer to the first argument and its length starting at p. Returns
+ * the number of bytes to skip to get to the following argument. */
+static char *nextArgument(char *start, char **str, size_t *len) {
+    char *p = start;
+    if (p[0] != '$') {
+        p = strchr(p,'$');
+        if (p == NULL) return NULL;
+    }
+
+    *len = (int)strtol(p+1,NULL,10);
+    p = strchr(p,'\r');
+    assert(p);
+    *str = p+2;
+    return p+2+(*len)+2;
+}
+
+/* Helper function for the redisAsyncCommand* family of functions. Writes a
+ * formatted command to the output buffer and registers the provided callback
+ * function with the context. */
 static int __redisAsyncCommand(redisAsyncContext *ac, redisCallbackFn *fn, void *privdata, char *cmd, size_t len) {
     redisContext *c = &(ac->c);
     redisCallback cb;
+    int pvariant, hasnext;
+    char *cstr, *astr;
+    size_t clen, alen;
+    char *p;
+    sds sname;
 
-    /* Don't accept new commands when the connection is lazily closed. */
-    if (c->flags & REDIS_DISCONNECTING) return REDIS_ERR;
-    __redisAppendCommand(c,cmd,len);
+    /* Don't accept new commands when the connection is about to be closed. */
+    if (c->flags & (REDIS_DISCONNECTING | REDIS_FREEING)) return REDIS_ERR;
 
-    /* Store callback */
+    /* Setup callback */
     cb.fn = fn;
     cb.privdata = privdata;
-    __redisPushCallback(&ac->replies,&cb);
+
+    /* Find out which command will be appended. */
+    p = nextArgument(cmd,&cstr,&clen);
+    assert(p != NULL);
+    hasnext = (p[0] == '$');
+    pvariant = (tolower(cstr[0]) == 'p') ? 1 : 0;
+    cstr += pvariant;
+    clen -= pvariant;
+
+    if (hasnext && strncasecmp(cstr,"subscribe\r\n",11) == 0) {
+        c->flags |= REDIS_SUBSCRIBED;
+
+        /* Add every channel/pattern to the list of subscription callbacks. */
+        while ((p = nextArgument(p,&astr,&alen)) != NULL) {
+            sname = sdsnewlen(astr,alen);
+            if (pvariant)
+                dictReplace(ac->sub.patterns,sname,&cb);
+            else
+                dictReplace(ac->sub.channels,sname,&cb);
+        }
+    } else if (strncasecmp(cstr,"unsubscribe\r\n",13) == 0) {
+        /* It is only useful to call (P)UNSUBSCRIBE when the context is
+         * subscribed to one or more channels or patterns. */
+        if (!(c->flags & REDIS_SUBSCRIBED)) return REDIS_ERR;
+
+        /* (P)UNSUBSCRIBE does not have its own response: every channel or
+         * pattern that is unsubscribed will receive a message. This means we
+         * should not append a callback function for this command. */
+    } else {
+        if (c->flags & REDIS_SUBSCRIBED)
+            /* This will likely result in an error reply, but it needs to be
+             * received and passed to the callback. */
+            __redisPushCallback(&ac->sub.invalid,&cb);
+        else
+            __redisPushCallback(&ac->replies,&cb);
+    }
+
+    __redisAppendCommand(c,cmd,len);
 
     /* Always schedule a write when the write buffer is non-empty */
-    if (ac->evAddWrite) ac->evAddWrite(ac->_adapter_data);
+    if (ac->ev.addWrite) ac->ev.addWrite(ac->ev.data);
 
     return REDIS_OK;
 }