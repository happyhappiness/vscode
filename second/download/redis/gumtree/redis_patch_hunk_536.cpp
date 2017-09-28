         zfree(fds);
 
         closeListeningSockets(0);
         redisSetProcTitle("redis-rdb-to-slaves");
 
         retval = rdbSaveRioWithEOFMark(&slave_sockets,NULL);
-        if (retval == REDIS_OK && rioFlush(&slave_sockets) == 0)
-            retval = REDIS_ERR;
+        if (retval == C_OK && rioFlush(&slave_sockets) == 0)
+            retval = C_ERR;
 
-        if (retval == REDIS_OK) {
+        if (retval == C_OK) {
             size_t private_dirty = zmalloc_get_private_dirty();
 
             if (private_dirty) {
-                redisLog(REDIS_NOTICE,
+                serverLog(LL_NOTICE,
                     "RDB: %zu MB of memory used by copy-on-write",
                     private_dirty/(1024*1024));
             }
 
             /* If we are returning OK, at least one slave was served
              * with the RDB file as expected, so we need to send a report
