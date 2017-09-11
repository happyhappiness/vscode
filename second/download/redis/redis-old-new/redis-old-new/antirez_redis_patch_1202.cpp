@@ -383,6 +383,8 @@ long long addReplyReplicationBacklog(redisClient *c, long long offset) {
 int masterTryPartialResynchronization(redisClient *c) {
     long long psync_offset, psync_len;
     char *master_runid = c->argv[1]->ptr;
+    char buf[128];
+    int buflen;
 
     /* Is the runid of this master the same advertised by the wannabe slave
      * via PSYNC? If runid changed this master is a different instance and
@@ -418,7 +420,14 @@ int masterTryPartialResynchronization(redisClient *c) {
     c->flags |= REDIS_SLAVE;
     c->replstate = REDIS_REPL_ONLINE;
     listAddNodeTail(server.slaves,c);
-    addReplySds(c,sdsnew("+CONTINUE\r\n"));
+    /* We can't use the connection buffers since they are used to accumulate
+     * new commands at this stage. But we are sure the socket send buffer is
+     * emtpy so this write will never fail actually. */
+    buflen = snprintf(buf,sizeof(buf),"+CONTINUE\r\n");
+    if (write(c->fd,buf,buflen) != buflen) {
+        freeClientAsync(c);
+        return REDIS_OK;
+    }
     psync_len = addReplyReplicationBacklog(c,psync_offset);
     redisLog(REDIS_NOTICE,
         "Partial resynchronization request accepted. Sending %lld bytes of backlog starting from offset %lld.", psync_len, psync_offset);
@@ -434,10 +443,13 @@ int masterTryPartialResynchronization(redisClient *c) {
     /* Add 1 to psync_offset if it the replication backlog does not exists
      * as when it will be created later we'll increment the offset by one. */
     if (server.repl_backlog == NULL) psync_offset++;
-    addReplySds(c,
-        sdscatprintf(sdsempty(),"+FULLRESYNC %s %lld\r\n",
-        server.runid,
-        psync_offset));
+    /* Again, we can't use the connection buffers (see above). */
+    buflen = snprintf(buf,sizeof(buf),"+FULLRESYNC %s %lld\r\n",
+                      server.runid,psync_offset);
+    if (write(c->fd,buf,buflen) != buflen) {
+        freeClientAsync(c);
+        return REDIS_OK;
+    }
     return REDIS_ERR;
 }
 