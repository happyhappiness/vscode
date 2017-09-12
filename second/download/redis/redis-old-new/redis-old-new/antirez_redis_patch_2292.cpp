@@ -5071,6 +5071,11 @@ static int syncWithMaster(void) {
             strerror(errno));
         return REDIS_ERR;
     }
+    if (buf[0] != '$') {
+        close(fd);
+        redisLog(REDIS_WARNING,"Bad protocol from MASTER, the first byte is not '$', are you sure the host and port are right?");
+        return REDIS_ERR;
+    }
     dumpsize = atoi(buf+1);
     redisLog(REDIS_NOTICE,"Receiving %d bytes data dump from MASTER",dumpsize);
     /* Read the bulk write data on a temp file */