@@ -767,6 +767,19 @@ int processMultibulkBuffer(redisClient *c) {
             }
 
             pos += newline-(c->querybuf+pos)+2;
+            #if 1
+            if (ll > 4096) {
+                /* If we are going to read a large object from network
+                 * try to make it likely that it will start at c->querybuf
+                 * boundary so that we can optimized object creation
+                 * avoiding a large copy of data. */
+                c->querybuf = sdsrange(c->querybuf,pos,-1);
+                pos = 0;
+            }
+            #endif
+            /* Hint the sds library about the amount of bytes this string is
+             * going to contain. */
+            if (ll > 4096) c->querybuf = sdsMakeRoomFor(c->querybuf,ll+2);
             c->bulklen = ll;
         }
 
@@ -779,9 +792,10 @@ int processMultibulkBuffer(redisClient *c) {
              * instead of creating a new object by *copying* the sds we
              * just use the current sds string. */
             if (pos == 0 &&
-                sdslen(c->querybuf) > 4096 &&
+                /* sdslen(c->querybuf) > 4096 && */
                 (signed) sdslen(c->querybuf) == c->bulklen+2)
             {
+                // printf("HERE (arg %d)\n",c->argc);
                 c->argv[c->argc++] = createObject(REDIS_STRING,c->querybuf);
                 sdsIncrLen(c->querybuf,-2); /* remove CRLF */
                 c->querybuf = sdsempty();
@@ -790,6 +804,7 @@ int processMultibulkBuffer(redisClient *c) {
                 c->querybuf = sdsMakeRoomFor(c->querybuf,c->bulklen+2);
                 pos = 0;
             } else {
+                // printf("NOT HERE (arg %d) (pos %d)\n",c->argc, pos);
                 c->argv[c->argc++] =
                     createStringObject(c->querybuf+pos,c->bulklen);
                 pos += c->bulklen+2;
@@ -850,14 +865,31 @@ void processInputBuffer(redisClient *c) {
 
 void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
     redisClient *c = (redisClient*) privdata;
-    int nread;
+    int nread, readlen;
     size_t qblen;
     REDIS_NOTUSED(el);
     REDIS_NOTUSED(mask);
 
+    readlen = REDIS_IOBUF_LEN;
+    /* If this is a multi bulk request, and we are processing a bulk reply
+     * that is large enough, try to maximize the probabilty that the query
+     * buffer contains excatly the SDS string representing the object, even
+     * at the risk of requring more read(2) calls. This way the function
+     * processMultiBulkBuffer() can avoid copying buffers to create the
+     * Redis Object representing the argument. */
+    #if 1
+    if (c->reqtype == REDIS_REQ_MULTIBULK && c->multibulklen && c->bulklen != -1
+        && c->bulklen > 4096)
+    {
+        int remaining = (unsigned)(c->bulklen+2)-sdslen(c->querybuf);
+
+        if (remaining < readlen) readlen = remaining;
+    }
+    #endif
+
     qblen = sdslen(c->querybuf);
-    c->querybuf = sdsMakeRoomFor(c->querybuf, REDIS_IOBUF_LEN);
-    nread = read(fd, c->querybuf+qblen, REDIS_IOBUF_LEN);
+    c->querybuf = sdsMakeRoomFor(c->querybuf, readlen);
+    nread = read(fd, c->querybuf+qblen, readlen);
     if (nread == -1) {
         if (errno == EAGAIN) {
             nread = 0;