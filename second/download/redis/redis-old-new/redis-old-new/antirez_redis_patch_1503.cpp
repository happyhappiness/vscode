@@ -767,19 +767,20 @@ int processMultibulkBuffer(redisClient *c) {
             }
 
             pos += newline-(c->querybuf+pos)+2;
-            #if 1
-            if (ll > 4096) {
+#ifdef REDIS_MBULK_BIG_ARG
+            if (ll >= REDIS_MBULK_BIG_ARG) {
                 /* If we are going to read a large object from network
                  * try to make it likely that it will start at c->querybuf
                  * boundary so that we can optimized object creation
                  * avoiding a large copy of data. */
                 c->querybuf = sdsrange(c->querybuf,pos,-1);
                 pos = 0;
             }
-            #endif
             /* Hint the sds library about the amount of bytes this string is
              * going to contain. */
-            if (ll > 4096) c->querybuf = sdsMakeRoomFor(c->querybuf,ll+2);
+            if (ll >= REDIS_MBULK_BIG_ARG)
+                c->querybuf = sdsMakeRoomFor(c->querybuf,ll+2);
+#endif
             c->bulklen = ll;
         }
 
@@ -791,8 +792,9 @@ int processMultibulkBuffer(redisClient *c) {
             /* Optimization: if the buffer contanins JUST our bulk element
              * instead of creating a new object by *copying* the sds we
              * just use the current sds string. */
+#ifdef REDIS_MBULK_BIG_ARG
             if (pos == 0 &&
-                /* sdslen(c->querybuf) > 4096 && */
+                c->bulklen >= REDIS_MBULK_BIG_ARG &&
                 (signed) sdslen(c->querybuf) == c->bulklen+2)
             {
                 // printf("HERE (arg %d)\n",c->argc);
@@ -804,11 +806,14 @@ int processMultibulkBuffer(redisClient *c) {
                 c->querybuf = sdsMakeRoomFor(c->querybuf,c->bulklen+2);
                 pos = 0;
             } else {
+#endif
                 // printf("NOT HERE (arg %d) (pos %d)\n",c->argc, pos);
                 c->argv[c->argc++] =
                     createStringObject(c->querybuf+pos,c->bulklen);
                 pos += c->bulklen+2;
+#ifdef REDIS_MBULK_BIG_ARG
             }
+#endif
             c->bulklen = -1;
             c->multibulklen--;
         }
@@ -871,21 +876,21 @@ void readQueryFromClient(aeEventLoop *el, int fd, void *privdata, int mask) {
     REDIS_NOTUSED(mask);
 
     readlen = REDIS_IOBUF_LEN;
+#if REDIS_MBULK_BIG_ARG
     /* If this is a multi bulk request, and we are processing a bulk reply
      * that is large enough, try to maximize the probabilty that the query
      * buffer contains excatly the SDS string representing the object, even
      * at the risk of requring more read(2) calls. This way the function
      * processMultiBulkBuffer() can avoid copying buffers to create the
      * Redis Object representing the argument. */
-    #if 1
     if (c->reqtype == REDIS_REQ_MULTIBULK && c->multibulklen && c->bulklen != -1
-        && c->bulklen > 4096)
+        && c->bulklen >= REDIS_MBULK_BIG_ARG)
     {
         int remaining = (unsigned)(c->bulklen+2)-sdslen(c->querybuf);
 
         if (remaining < readlen) readlen = remaining;
     }
-    #endif
+#endif
 
     qblen = sdslen(c->querybuf);
     c->querybuf = sdsMakeRoomFor(c->querybuf, readlen);