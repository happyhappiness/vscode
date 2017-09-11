@@ -372,6 +372,11 @@ void redisProcessCallbacks(redisAsyncContext *ac) {
                 __redisAsyncDisconnect(ac);
                 return;
             }
+            
+            /* If monitor mode, repush callback */
+            if(c->flags & REDIS_MONITORING) {
+                __redisPushCallback(&ac->replies,&cb);
+            }
 
             /* When the connection is not being disconnected, simply stop
              * trying to get replies and wait for the next loop tick. */
@@ -381,22 +386,31 @@ void redisProcessCallbacks(redisAsyncContext *ac) {
         /* Even if the context is subscribed, pending regular callbacks will
          * get a reply before pub/sub messages arrive. */
         if (__redisShiftCallback(&ac->replies,&cb) != REDIS_OK) {
-            /* A spontaneous reply in a not-subscribed context can only be the
-             * error reply that is sent when a new connection exceeds the
-             * maximum number of allowed connections on the server side. This
-             * is seen as an error instead of a regular reply because the
-             * server closes the connection after sending it. To prevent the
-             * error from being overwritten by an EOF error the connection is
-             * closed here. See issue #43. */
-            if ( !(c->flags & REDIS_SUBSCRIBED) && ((redisReply*)reply)->type == REDIS_REPLY_ERROR ) {
+            /*
+             * A spontaneous reply in a not-subscribed context can be the error
+             * reply that is sent when a new connection exceeds the maximum
+             * number of allowed connections on the server side.
+             *
+             * This is seen as an error instead of a regular reply because the
+             * server closes the connection after sending it.
+             *
+             * To prevent the error from being overwritten by an EOF error the
+             * connection is closed here. See issue #43.
+             *
+             * Another possibility is that the server is loading its dataset.
+             * In this case we also want to close the connection, and have the
+             * user wait until the server is ready to take our request.
+             */
+            if (((redisReply*)reply)->type == REDIS_REPLY_ERROR) {
                 c->err = REDIS_ERR_OTHER;
                 snprintf(c->errstr,sizeof(c->errstr),"%s",((redisReply*)reply)->str);
                 __redisAsyncDisconnect(ac);
                 return;
             }
-            /* No more regular callbacks and no errors, the context *must* be subscribed. */
-            assert(c->flags & REDIS_SUBSCRIBED);
-            __redisGetSubscribeCallback(ac,reply,&cb);
+            /* No more regular callbacks and no errors, the context *must* be subscribed or monitoring. */
+            assert((c->flags & REDIS_SUBSCRIBED || c->flags & REDIS_MONITORING));
+            if(c->flags & REDIS_SUBSCRIBED)
+                __redisGetSubscribeCallback(ac,reply,&cb);
         }
 
         if (cb.fn != NULL) {
@@ -557,6 +571,10 @@ static int __redisAsyncCommand(redisAsyncContext *ac, redisCallbackFn *fn, void
         /* (P)UNSUBSCRIBE does not have its own response: every channel or
          * pattern that is unsubscribed will receive a message. This means we
          * should not append a callback function for this command. */
+     } else if(strncasecmp(cstr,"monitor\r\n",9) == 0) {
+         /* Set monitor flag and push callback */
+         c->flags |= REDIS_MONITORING;
+         __redisPushCallback(&ac->replies,&cb);
     } else {
         if (c->flags & REDIS_SUBSCRIBED)
             /* This will likely result in an error reply, but it needs to be