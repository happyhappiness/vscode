@@ -364,6 +364,7 @@ void sortCommand(redisClient *c) {
          * SORT result is empty a new key is set and maybe the old content
          * replaced. */
         server.dirty += 1+outputlen;
+        touchWatchedKey(c->db,storekey);
         addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",outputlen));
     }
 