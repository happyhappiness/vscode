         }
         while((n = n/10) != 0) {
             len++;
         }
     }
 
-    if (len < REDIS_SHARED_BULKHDR_LEN)
+    if (len < OBJ_SHARED_BULKHDR_LEN)
         addReply(c,shared.bulkhdr[len]);
     else
         addReplyLongLongWithPrefix(c,len,'$');
 }
 
 /* Add a Redis Object as a bulk reply */
-void addReplyBulk(redisClient *c, robj *obj) {
+void addReplyBulk(client *c, robj *obj) {
     addReplyBulkLen(c,obj);
     addReply(c,obj);
     addReply(c,shared.crlf);
 }
 
 /* Add a C buffer as bulk reply */
-void addReplyBulkCBuffer(redisClient *c, void *p, size_t len) {
+void addReplyBulkCBuffer(client *c, const void *p, size_t len) {
     addReplyLongLongWithPrefix(c,len,'$');
     addReplyString(c,p,len);
     addReply(c,shared.crlf);
 }
 
+/* Add sds to reply (takes ownership of sds and frees it) */
+void addReplyBulkSds(client *c, sds s)  {
+    addReplySds(c,sdscatfmt(sdsempty(),"$%u\r\n",
+        (unsigned long)sdslen(s)));
+    addReplySds(c,s);
+    addReply(c,shared.crlf);
+}
+
 /* Add a C nul term string as bulk reply */
-void addReplyBulkCString(redisClient *c, char *s) {
+void addReplyBulkCString(client *c, const char *s) {
     if (s == NULL) {
         addReply(c,shared.nullbulk);
     } else {
         addReplyBulkCBuffer(c,s,strlen(s));
     }
 }
 
 /* Add a long long as a bulk reply */
-void addReplyBulkLongLong(redisClient *c, long long ll) {
+void addReplyBulkLongLong(client *c, long long ll) {
     char buf[64];
     int len;
 
     len = ll2string(buf,64,ll);
     addReplyBulkCBuffer(c,buf,len);
 }
 
 /* Copy 'src' client output buffers into 'dst' client output buffers.
  * The function takes care of freeing the old output buffers of the
  * destination client. */
-void copyClientOutputBuffer(redisClient *dst, redisClient *src) {
+void copyClientOutputBuffer(client *dst, client *src) {
     listRelease(dst->reply);
     dst->reply = listDup(src->reply);
     memcpy(dst->buf,src->buf,src->bufpos);
     dst->bufpos = src->bufpos;
     dst->reply_bytes = src->reply_bytes;
 }
 
+/* Return true if the specified client has pending reply buffers to write to
+ * the socket. */
+int clientHasPendingReplies(client *c) {
+    return c->bufpos || listLength(c->reply);
+}
+
 #define MAX_ACCEPTS_PER_CALL 1000
-static void acceptCommonHandler(int fd, int flags) {
-    redisClient *c;
+static void acceptCommonHandler(int fd, int flags, char *ip) {
+    client *c;
     if ((c = createClient(fd)) == NULL) {
-        redisLog(REDIS_WARNING,
+        serverLog(LL_WARNING,
             "Error registering fd event for the new client: %s (fd=%d)",
             strerror(errno),fd);
         close(fd); /* May be already closed, just ignore errors */
         return;
     }
     /* If maxclient directive is set and this is one client more... close the
