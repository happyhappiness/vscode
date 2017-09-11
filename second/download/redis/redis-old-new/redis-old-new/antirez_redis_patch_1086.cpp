@@ -1153,7 +1153,7 @@ void clusterWriteHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
         handleLinkIOError(link);
         return;
     }
-    link->sndbuf = sdsrange(link->sndbuf,nwritten,-1);
+    sdsrange(link->sndbuf,nwritten,-1);
     if (sdslen(link->sndbuf) == 0)
         aeDeleteFileEvent(server.el, link->fd, AE_WRITABLE);
 }