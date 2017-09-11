@@ -1169,53 +1169,52 @@ void clusterReadHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
     REDIS_NOTUSED(el);
     REDIS_NOTUSED(mask);
 
-again:
-    rcvbuflen = sdslen(link->rcvbuf);
-    if (rcvbuflen < 4) {
-        /* First, obtain the first four bytes to get the full message
-         * length. */
-        readlen = 4 - rcvbuflen;
-    } else {
-        /* Finally read the full message. */
-        hdr = (clusterMsg*) link->rcvbuf;
-        if (rcvbuflen == 4) {
-            /* Perform some sanity check on the message length. */
-            if (ntohl(hdr->totlen) < CLUSTERMSG_MIN_LEN) {
-                redisLog(REDIS_WARNING,
-                    "Bad message length received from Cluster bus.");
-                handleLinkIOError(link);
-                return;
+    while(1) { /* Read as long as there is data to read. */
+        rcvbuflen = sdslen(link->rcvbuf);
+        if (rcvbuflen < 4) {
+            /* First, obtain the first four bytes to get the full message
+             * length. */
+            readlen = 4 - rcvbuflen;
+        } else {
+            /* Finally read the full message. */
+            hdr = (clusterMsg*) link->rcvbuf;
+            if (rcvbuflen == 4) {
+                /* Perform some sanity check on the message length. */
+                if (ntohl(hdr->totlen) < CLUSTERMSG_MIN_LEN) {
+                    redisLog(REDIS_WARNING,
+                        "Bad message length received from Cluster bus.");
+                    handleLinkIOError(link);
+                    return;
+                }
             }
+            readlen = ntohl(hdr->totlen) - rcvbuflen;
+            if (readlen > sizeof(buf)) readlen = sizeof(buf);
         }
-        readlen = ntohl(hdr->totlen) - rcvbuflen;
-    }
 
-    nread = read(fd,buf,readlen);
-    if (nread == -1 && errno == EAGAIN) return; /* No more data ready. */
+        nread = read(fd,buf,readlen);
+        if (nread == -1 && errno == EAGAIN) return; /* No more data ready. */
 
-    if (nread <= 0) {
-        /* I/O error... */
-        redisLog(REDIS_DEBUG,"I/O error reading from node link: %s",
-            (nread == 0) ? "connection closed" : strerror(errno));
-        handleLinkIOError(link);
-        return;
-    } else {
-        /* Read data and recast the pointer to the new buffer. */
-        link->rcvbuf = sdscatlen(link->rcvbuf,buf,nread);
-        hdr = (clusterMsg*) link->rcvbuf;
-        rcvbuflen += nread;
-    }
-
-    /* Total length obtained? read the payload now instead of burning
-     * cycles waiting for a new event to fire. */
-    if (rcvbuflen == 4) goto again;
-
-    /* Whole packet in memory? We can process it. */
-    if (rcvbuflen == ntohl(hdr->totlen)) {
-        if (clusterProcessPacket(link)) {
-            sdsfree(link->rcvbuf);
-            link->rcvbuf = sdsempty();
-            rcvbuflen = 0; /* Useless line of code currently... defensive. */
+        if (nread <= 0) {
+            /* I/O error... */
+            redisLog(REDIS_DEBUG,"I/O error reading from node link: %s",
+                (nread == 0) ? "connection closed" : strerror(errno));
+            handleLinkIOError(link);
+            return;
+        } else {
+            /* Read data and recast the pointer to the new buffer. */
+            link->rcvbuf = sdscatlen(link->rcvbuf,buf,nread);
+            hdr = (clusterMsg*) link->rcvbuf;
+            rcvbuflen += nread;
+        }
+
+        /* Total length obtained? Process this packet. */
+        if (rcvbuflen >= 4 && rcvbuflen == ntohl(hdr->totlen)) {
+            if (clusterProcessPacket(link)) {
+                sdsfree(link->rcvbuf);
+                link->rcvbuf = sdsempty();
+            } else {
+                return; /* Link no longer valid. */
+            }
         }
     }
 }