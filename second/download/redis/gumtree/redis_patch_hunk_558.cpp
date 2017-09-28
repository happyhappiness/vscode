             return;
         }
     }
 
     /* If the preamble was already transfered, send the RDB bulk data. */
     lseek(slave->repldbfd,slave->repldboff,SEEK_SET);
-    buflen = read(slave->repldbfd,buf,REDIS_IOBUF_LEN);
+    buflen = read(slave->repldbfd,buf,PROTO_IOBUF_LEN);
     if (buflen <= 0) {
-        redisLog(REDIS_WARNING,"Read error sending DB to slave: %s",
+        serverLog(LL_WARNING,"Read error sending DB to slave: %s",
             (buflen == 0) ? "premature EOF" : strerror(errno));
         freeClient(slave);
         return;
     }
     if ((nwritten = write(fd,buf,buflen)) == -1) {
         if (errno != EAGAIN) {
-            redisLog(REDIS_WARNING,"Write error sending DB to slave: %s",
+            serverLog(LL_WARNING,"Write error sending DB to slave: %s",
                 strerror(errno));
             freeClient(slave);
         }
         return;
     }
     slave->repldboff += nwritten;
