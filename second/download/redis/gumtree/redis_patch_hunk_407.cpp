         }
 
         /* Rename the temporary file. This will not unlink the target file if
          * it exists, because we reference it with "oldfd". */
         latencyStartMonitor(latency);
         if (rename(tmpfile,server.aof_filename) == -1) {
-            redisLog(REDIS_WARNING,
-                "Error trying to rename the temporary AOF file: %s", strerror(errno));
+            serverLog(LL_WARNING,
+                "Error trying to rename the temporary AOF file %s into %s: %s",
+                tmpfile,
+                server.aof_filename,
+                strerror(errno));
             close(newfd);
             if (oldfd != -1) close(oldfd);
             goto cleanup;
         }
         latencyEndMonitor(latency);
         latencyAddSampleIfNeeded("aof-rename",latency);
