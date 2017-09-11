@@ -1514,7 +1514,7 @@ void sentinelFlushConfig(void) {
             close(fd);
         }
     } else {
-        redisLog(REDIS_WARNING,"WARNING: Senitnel was not able to save the new configuration on disk!!!: %s", strerror(errno));
+        redisLog(REDIS_WARNING,"WARNING: Sentinel was not able to save the new configuration on disk!!!: %s", strerror(errno));
     }
     server.hz = saved_hz;
     return;