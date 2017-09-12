@@ -369,7 +369,7 @@ void sortCommand(redisClient *c) {
          * replaced. */
         server.dirty += 1+outputlen;
         touchWatchedKey(c->db,storekey);
-        addReplySds(c,sdscatprintf(sdsempty(),":%d\r\n",outputlen));
+        addReplyLongLong(c,outputlen);
     }
 
     /* Cleanup */