@@ -206,16 +206,27 @@ static void clientDone(client c) {
     }
 }
 
+/* Read a length from the buffer pointed to by *p, store the length in *len,
+ * and return the number of bytes that the cursor advanced. */
+static int readLen(char *p, int *len) {
+    char *tail = strstr(p,"\r\n");
+    if (tail == NULL)
+        return 0;
+    *tail = '\0';
+    *len = atoi(p+1);
+    return tail+2-p;
+}
+
 static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask)
 {
-    char buf[1024];
-    int nread;
+    char buf[1024], *p;
+    int nread, pos=0, len=0;
     client c = privdata;
     REDIS_NOTUSED(el);
     REDIS_NOTUSED(fd);
     REDIS_NOTUSED(mask);
 
-    nread = read(c->fd, buf, 1024);
+    nread = read(c->fd,buf,sizeof(buf));
     if (nread == -1) {
         fprintf(stderr, "Reading from socket: %s\n", strerror(errno));
         freeClient(c);
@@ -228,82 +239,89 @@ static void readHandler(aeEventLoop *el, int fd, void *privdata, int mask)
     }
     c->totreceived += nread;
     c->ibuf = sdscatlen(c->ibuf,buf,nread);
+    len = sdslen(c->ibuf);
 
-processdata:
-    /* Are we waiting for the first line of the command of for  sdf 
-     * count in bulk or multi bulk operations? */
     if (c->replytype == REPLY_INT ||
-        c->replytype == REPLY_RETCODE ||
-        (c->replytype == REPLY_BULK && c->readlen == -1) ||
-        (c->replytype == REPLY_MBULK && c->readlen == -1) ||
-        (c->replytype == REPLY_MBULK && c->mbulk == -1)) {
-        char *p;
-
-        /* Check if the first line is complete. This is only true if
-         * there is a newline inside the buffer. */
-        if ((p = strchr(c->ibuf,'\n')) != NULL) {
-            if (c->replytype == REPLY_BULK ||
-                (c->replytype == REPLY_MBULK && c->mbulk != -1))
-            {
-                /* Read the count of a bulk reply (being it a single bulk or
-                 * a multi bulk reply). "$<count>" for the protocol spec. */
-                *p = '\0';
-                *(p-1) = '\0';
-                c->readlen = atoi(c->ibuf+1)+2;
-                // printf("BULK ATOI: %s\n", c->ibuf+1);
-                /* Handle null bulk reply "$-1" */
-                if (c->readlen-2 == -1) {
-                    clientDone(c);
-                    return;
-                }
-                /* Leave all the rest in the input buffer */
-                c->ibuf = sdsrange(c->ibuf,(p-c->ibuf)+1,-1);
-                /* fall through to reach the point where the code will try
-                 * to check if the bulk reply is complete. */
-            } else if (c->replytype == REPLY_MBULK && c->mbulk == -1) {
-                /* Read the count of a multi bulk reply. That is, how many
-                 * bulk replies we have to read next. "*<count>" protocol. */
-                *p = '\0';
-                *(p-1) = '\0';
-                c->mbulk = atoi(c->ibuf+1);
-                /* Handle null bulk reply "*-1" */
-                if (c->mbulk == -1) {
-                    clientDone(c);
-                    return;
+        c->replytype == REPLY_RETCODE)
+    {
+        /* Check if the first line is complete. This is everything we need
+         * when waiting for an integer or status code reply.*/
+        if ((p = strstr(c->ibuf,"\r\n")) != NULL)
+            goto done;
+    } else if (c->replytype == REPLY_BULK) {
+        int advance = 0;
+        if (c->readlen < 0) {
+            advance = readLen(c->ibuf+pos,&c->readlen);
+            if (advance) {
+                pos += advance;
+                if (c->readlen == -1) {
+                    goto done;
+                } else {
+                    /* include the trailing \r\n */
+                    c->readlen += 2;
                 }
-                // printf("%p) %d elements list\n", c, c->mbulk);
-                /* Leave all the rest in the input buffer */
-                c->ibuf = sdsrange(c->ibuf,(p-c->ibuf)+1,-1);
-                goto processdata;
             } else {
-                c->ibuf = sdstrim(c->ibuf,"\r\n");
-                clientDone(c);
-                return;
+                goto skip;
             }
         }
-    }
-    /* bulk read, did we read everything? */
-    if (((c->replytype == REPLY_MBULK && c->mbulk != -1) || 
-         (c->replytype == REPLY_BULK)) && c->readlen != -1 &&
-          (unsigned)c->readlen <= sdslen(c->ibuf))
-    {
-        // printf("BULKSTATUS mbulk:%d readlen:%d sdslen:%d\n",
-        //    c->mbulk,c->readlen,sdslen(c->ibuf));
-        if (c->replytype == REPLY_BULK) {
-            clientDone(c);
-        } else if (c->replytype == REPLY_MBULK) {
-            // printf("%p) %d (%d)) ",c, c->mbulk, c->readlen);
-            // fwrite(c->ibuf,c->readlen,1,stdout);
-            // printf("\n");
-            if (--c->mbulk == 0) {
-                clientDone(c);
+
+        int canconsume;
+        if (c->readlen > 0) {
+            canconsume = c->readlen > (len-pos) ? (len-pos) : c->readlen;
+            c->readlen -= canconsume;
+            pos += canconsume;
+        }
+
+        if (c->readlen == 0)
+            goto done;
+    } else if (c->replytype == REPLY_MBULK) {
+        int advance = 0;
+        if (c->mbulk == -1) {
+            advance = readLen(c->ibuf+pos,&c->mbulk);
+            if (advance) {
+                pos += advance;
+                if (c->mbulk == -1)
+                    goto done;
+            } else {
+                goto skip;
+            }
+        }
+
+        int canconsume;
+        while(c->mbulk > 0 && pos < len) {
+            if (c->readlen > 0) {
+                canconsume = c->readlen > (len-pos) ? (len-pos) : c->readlen;
+                c->readlen -= canconsume;
+                pos += canconsume;
+                if (c->readlen == 0)
+                    c->mbulk--;
             } else {
-                c->ibuf = sdsrange(c->ibuf,c->readlen,-1);
-                c->readlen = -1;
-                goto processdata;
+                advance = readLen(c->ibuf+pos,&c->readlen);
+                if (advance) {
+                    pos += advance;
+                    if (c->readlen == -1) {
+                        c->mbulk--;
+                        continue;
+                    } else {
+                        /* include the trailing \r\n */
+                        c->readlen += 2;
+                    }
+                } else {
+                    goto skip;
+                }
             }
         }
+
+        if (c->mbulk == 0)
+            goto done;
     }
+
+skip:
+    c->ibuf = sdsrange(c->ibuf,pos,-1);
+    return;
+done:
+    clientDone(c);
+    return;
 }
 
 static void writeHandler(aeEventLoop *el, int fd, void *privdata, int mask)