         if (server.maxmemory) {
             if (server.maxmemory < zmalloc_used_memory()) {
                 redisLog(REDIS_WARNING,"WARNING: the new maxmemory value set via CONFIG SET is smaller than the current memory usage. This will result in keys eviction and/or inability to accept new write commands depending on the maxmemory-policy.");
             }
             freeMemoryIfNeeded();
         }
+    } else if (!strcasecmp(c->argv[2]->ptr,"maxclients")) {
+        int orig_value = server.maxclients;
+
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
+
+        /* Try to check if the OS is capable of supporting so many FDs. */
+        server.maxclients = ll;
+        if (ll > orig_value) {
+            adjustOpenFilesLimit();
+            if (server.maxclients != ll) {
+                addReplyErrorFormat(c,"The operating system is not able to handle the specified number of clients, try with %d", server.maxclients);
+                server.maxclients = orig_value;
+                return;
+            }
+            if (aeGetSetSize(server.el) <
+                server.maxclients + REDIS_EVENTLOOP_FDSET_INCR)
+            {
+                if (aeResizeSetSize(server.el,
+                    server.maxclients + REDIS_EVENTLOOP_FDSET_INCR) == AE_ERR)
+                {
+                    addReplyError(c,"The event loop API used by Redis is not able to handle the specified number of clients");
+                    server.maxclients = orig_value;
+                    return;
+                }
+            }
+        }
     } else if (!strcasecmp(c->argv[2]->ptr,"hz")) {
-        if (getLongLongFromObject(o,&ll) == REDIS_ERR ||
-            ll < 0) goto badfmt;
-        server.hz = (int) ll;
+        if (getLongLongFromObject(o,&ll) == REDIS_ERR || ll < 0) goto badfmt;
+        server.hz = ll;
         if (server.hz < REDIS_MIN_HZ) server.hz = REDIS_MIN_HZ;
         if (server.hz > REDIS_MAX_HZ) server.hz = REDIS_MAX_HZ;
     } else if (!strcasecmp(c->argv[2]->ptr,"maxmemory-policy")) {
         if (!strcasecmp(o->ptr,"volatile-lru")) {
             server.maxmemory_policy = REDIS_MAXMEMORY_VOLATILE_LRU;
         } else if (!strcasecmp(o->ptr,"volatile-random")) {
