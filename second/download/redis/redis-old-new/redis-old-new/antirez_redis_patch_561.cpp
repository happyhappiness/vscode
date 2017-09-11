@@ -969,7 +969,23 @@ instanceLink *releaseInstanceLink(instanceLink *link, sentinelRedisInstance *ri)
     link->refcount--;
     if (link->refcount != 0) {
         if (ri) {
-            /* TODO: run the callbacks list and rebind. */
+            /* This instance may have pending callbacks in the hiredis async
+             * context, having as 'privdata' the instance that we are going to
+             * free. Let's rewrite the callback list, directly exploiting
+             * hiredis internal data structures, in order to bind them with
+             * a callback that will ignore the reply at all. */
+            redisCallback *cb;
+            redisCallbackList *callbacks = &link->cc->replies;
+
+            cb = callbacks->head;
+            while(cb) {
+                if (cb->privdata == ri) {
+                    printf("HERE\n");
+                    cb->fn = sentinelDiscardReplyCallback;
+                    cb->privdata = NULL; /* Not strictly needed. */
+                }
+                cb = cb->next;
+            }
         }
         return link; /* Other active users. */
     }