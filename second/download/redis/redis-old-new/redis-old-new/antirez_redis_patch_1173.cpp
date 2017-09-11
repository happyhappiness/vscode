@@ -2736,7 +2736,7 @@ void loadDataFromDisk(void) {
             redisLog(REDIS_NOTICE,"DB loaded from disk: %.3f seconds",
                 (float)(ustime()-start)/1000000);
         } else if (errno != ENOENT) {
-            redisLog(REDIS_WARNING,"Fatal error loading the DB. Exiting.");
+            redisLog(REDIS_WARNING,"Fatal error loading the DB: %s. Exiting.",strerror(errno));
             exit(1);
         }
     }