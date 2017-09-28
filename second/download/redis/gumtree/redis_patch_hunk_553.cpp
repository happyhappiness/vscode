          * static buffer if any (from j to argc). */
         for (j = 0; j < argc; j++)
             addReplyBulk(slave,argv[j]);
     }
 }
 
-void replicationFeedMonitors(redisClient *c, list *monitors, int dictid, robj **argv, int argc) {
+void replicationFeedMonitors(client *c, list *monitors, int dictid, robj **argv, int argc) {
     listNode *ln;
     listIter li;
     int j;
     sds cmdrepr = sdsnew("+");
     robj *cmdobj;
     struct timeval tv;
 
     gettimeofday(&tv,NULL);
     cmdrepr = sdscatprintf(cmdrepr,"%ld.%06ld ",(long)tv.tv_sec,(long)tv.tv_usec);
-    if (c->flags & REDIS_LUA_CLIENT) {
+    if (c->flags & CLIENT_LUA) {
         cmdrepr = sdscatprintf(cmdrepr,"[%d lua] ",dictid);
-    } else if (c->flags & REDIS_UNIX_SOCKET) {
+    } else if (c->flags & CLIENT_UNIX_SOCKET) {
         cmdrepr = sdscatprintf(cmdrepr,"[%d unix:%s] ",dictid,server.unixsocket);
     } else {
         cmdrepr = sdscatprintf(cmdrepr,"[%d %s] ",dictid,getClientPeerId(c));
     }
 
     for (j = 0; j < argc; j++) {
-        if (argv[j]->encoding == REDIS_ENCODING_INT) {
+        if (argv[j]->encoding == OBJ_ENCODING_INT) {
             cmdrepr = sdscatprintf(cmdrepr, "\"%ld\"", (long)argv[j]->ptr);
         } else {
             cmdrepr = sdscatrepr(cmdrepr,(char*)argv[j]->ptr,
                         sdslen(argv[j]->ptr));
         }
         if (j != argc-1)
             cmdrepr = sdscatlen(cmdrepr," ",1);
     }
     cmdrepr = sdscatlen(cmdrepr,"\r\n",2);
-    cmdobj = createObject(REDIS_STRING,cmdrepr);
+    cmdobj = createObject(OBJ_STRING,cmdrepr);
 
     listRewind(monitors,&li);
     while((ln = listNext(&li))) {
-        redisClient *monitor = ln->value;
+        client *monitor = ln->value;
         addReply(monitor,cmdobj);
     }
     decrRefCount(cmdobj);
 }
 
 /* Feed the slave 'c' with the replication backlog starting from the
  * specified 'offset' up to the end of the backlog. */
-long long addReplyReplicationBacklog(redisClient *c, long long offset) {
+long long addReplyReplicationBacklog(client *c, long long offset) {
     long long j, skip, len;
 
-    redisLog(REDIS_DEBUG, "[PSYNC] Slave request offset: %lld", offset);
+    serverLog(LL_DEBUG, "[PSYNC] Slave request offset: %lld", offset);
 
     if (server.repl_backlog_histlen == 0) {
-        redisLog(REDIS_DEBUG, "[PSYNC] Backlog history len is zero");
+        serverLog(LL_DEBUG, "[PSYNC] Backlog history len is zero");
         return 0;
     }
 
-    redisLog(REDIS_DEBUG, "[PSYNC] Backlog size: %lld",
+    serverLog(LL_DEBUG, "[PSYNC] Backlog size: %lld",
              server.repl_backlog_size);
-    redisLog(REDIS_DEBUG, "[PSYNC] First byte: %lld",
+    serverLog(LL_DEBUG, "[PSYNC] First byte: %lld",
              server.repl_backlog_off);
-    redisLog(REDIS_DEBUG, "[PSYNC] History len: %lld",
+    serverLog(LL_DEBUG, "[PSYNC] History len: %lld",
              server.repl_backlog_histlen);
-    redisLog(REDIS_DEBUG, "[PSYNC] Current index: %lld",
+    serverLog(LL_DEBUG, "[PSYNC] Current index: %lld",
              server.repl_backlog_idx);
 
     /* Compute the amount of bytes we need to discard. */
     skip = offset - server.repl_backlog_off;
-    redisLog(REDIS_DEBUG, "[PSYNC] Skipping: %lld", skip);
+    serverLog(LL_DEBUG, "[PSYNC] Skipping: %lld", skip);
 
     /* Point j to the oldest byte, that is actaully our
      * server.repl_backlog_off byte. */
     j = (server.repl_backlog_idx +
         (server.repl_backlog_size-server.repl_backlog_histlen)) %
         server.repl_backlog_size;
-    redisLog(REDIS_DEBUG, "[PSYNC] Index of first byte: %lld", j);
+    serverLog(LL_DEBUG, "[PSYNC] Index of first byte: %lld", j);
 
     /* Discard the amount of data to seek to the specified 'offset'. */
     j = (j + skip) % server.repl_backlog_size;
 
     /* Feed slave with data. Since it is a circular buffer we have to
      * split the reply in two parts if we are cross-boundary. */
     len = server.repl_backlog_histlen - skip;
-    redisLog(REDIS_DEBUG, "[PSYNC] Reply total length: %lld", len);
+    serverLog(LL_DEBUG, "[PSYNC] Reply total length: %lld", len);
     while(len) {
         long long thislen =
             ((server.repl_backlog_size - j) < len) ?
             (server.repl_backlog_size - j) : len;
 
-        redisLog(REDIS_DEBUG, "[PSYNC] addReply() length: %lld", thislen);
+        serverLog(LL_DEBUG, "[PSYNC] addReply() length: %lld", thislen);
         addReplySds(c,sdsnewlen(server.repl_backlog + j, thislen));
         len -= thislen;
         j = 0;
     }
     return server.repl_backlog_histlen - skip;
 }
