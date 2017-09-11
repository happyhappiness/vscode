@@ -1167,8 +1167,6 @@ int clusterProcessPacket(clusterLink *link) {
 
     /* Perform sanity checks */
     if (totlen < 16) return 1; /* At least signature, version, totlen, count. */
-    if (hdr->sig[0] != 'R' || hdr->sig[1] != 'C' ||
-        hdr->sig[2] != 'm' || hdr->sig[3] != 'b') return 1; /* Bad signature. */
     if (ntohs(hdr->ver) != 0) return 1; /* Can't handle versions other than 0. */
     if (totlen > sdslen(link->rcvbuf)) return 1;
     if (type == CLUSTERMSG_TYPE_PING || type == CLUSTERMSG_TYPE_PONG ||
@@ -1582,18 +1580,22 @@ void clusterReadHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
 
     while(1) { /* Read as long as there is data to read. */
         rcvbuflen = sdslen(link->rcvbuf);
-        if (rcvbuflen < 4) {
-            /* First, obtain the first four bytes to get the full message
+        if (rcvbuflen < 8) {
+            /* First, obtain the first 8 bytes to get the full message
              * length. */
-            readlen = 4 - rcvbuflen;
+            readlen = 8 - rcvbuflen;
         } else {
             /* Finally read the full message. */
             hdr = (clusterMsg*) link->rcvbuf;
-            if (rcvbuflen == 4) {
-                /* Perform some sanity check on the message length. */
-                if (ntohl(hdr->totlen) < CLUSTERMSG_MIN_LEN) {
+            if (rcvbuflen == 8) {
+                /* Perform some sanity check on the message signature
+                 * and length. */
+                if (memcmp(hdr->sig,"RCmb",4) != 0 ||
+                    ntohl(hdr->totlen) < CLUSTERMSG_MIN_LEN)
+                {
                     redisLog(REDIS_WARNING,
-                        "Bad message length received from Cluster bus.");
+                        "Bad message length or signature received "
+                        "from Cluster bus.");
                     handleLinkIOError(link);
                     return;
                 }
@@ -1619,7 +1621,7 @@ void clusterReadHandler(aeEventLoop *el, int fd, void *privdata, int mask) {
         }
 
         /* Total length obtained? Process this packet. */
-        if (rcvbuflen >= 4 && rcvbuflen == ntohl(hdr->totlen)) {
+        if (rcvbuflen >= 8 && rcvbuflen == ntohl(hdr->totlen)) {
             if (clusterProcessPacket(link)) {
                 sdsfree(link->rcvbuf);
                 link->rcvbuf = sdsempty();