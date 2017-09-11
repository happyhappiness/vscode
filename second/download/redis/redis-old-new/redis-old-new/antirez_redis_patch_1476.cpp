@@ -1501,10 +1501,14 @@ sds genRedisInfoString(char *section) {
             info = sdscatprintf(info,
                 "aof_current_size:%lld\r\n"
                 "aof_base_size:%lld\r\n"
-                "aof_pending_rewrite:%d\r\n",
+                "aof_pending_rewrite:%d\r\n"
+                "aof_buffer_length:%zu\r\n"
+                "aof_pending_bio_fsync:%llu\r\n",
                 (long long) server.appendonly_current_size,
                 (long long) server.auto_aofrewrite_base_size,
-                server.aofrewrite_scheduled);
+                server.aofrewrite_scheduled,
+                sdslen(server.aofbuf),
+                bioPendingJobsOfType(REDIS_BIO_AOF_FSYNC));
         }
 
         if (server.loading) {