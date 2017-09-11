@@ -175,7 +175,7 @@ robj *dupLastObjectIfNeeded(list *reply) {
  * Low level functions to add more data to output buffers.
  * -------------------------------------------------------------------------- */
 
-int _addReplyToBuffer(redisClient *c, char *s, size_t len) {
+int _addReplyToBuffer(redisClient *c, const char *s, size_t len) {
     size_t available = sizeof(c->buf)-c->bufpos;
 
     if (c->flags & REDIS_CLOSE_AFTER_REPLY) return REDIS_OK;
@@ -255,7 +255,7 @@ void _addReplySdsToList(redisClient *c, sds s) {
     asyncCloseClientOnOutputBufferLimitReached(c);
 }
 
-void _addReplyStringToList(redisClient *c, char *s, size_t len) {
+void _addReplyStringToList(redisClient *c, const char *s, size_t len) {
     robj *tail;
 
     if (c->flags & REDIS_CLOSE_AFTER_REPLY) return;
@@ -341,19 +341,19 @@ void addReplySds(redisClient *c, sds s) {
     }
 }
 
-void addReplyString(redisClient *c, char *s, size_t len) {
+void addReplyString(redisClient *c, const char *s, size_t len) {
     if (prepareClientToWrite(c) != REDIS_OK) return;
     if (_addReplyToBuffer(c,s,len) != REDIS_OK)
         _addReplyStringToList(c,s,len);
 }
 
-void addReplyErrorLength(redisClient *c, char *s, size_t len) {
+void addReplyErrorLength(redisClient *c, const char *s, size_t len) {
     addReplyString(c,"-ERR ",5);
     addReplyString(c,s,len);
     addReplyString(c,"\r\n",2);
 }
 
-void addReplyError(redisClient *c, char *err) {
+void addReplyError(redisClient *c, const char *err) {
     addReplyErrorLength(c,err,strlen(err));
 }
 
@@ -373,13 +373,13 @@ void addReplyErrorFormat(redisClient *c, const char *fmt, ...) {
     sdsfree(s);
 }
 
-void addReplyStatusLength(redisClient *c, char *s, size_t len) {
+void addReplyStatusLength(redisClient *c, const char *s, size_t len) {
     addReplyString(c,"+",1);
     addReplyString(c,s,len);
     addReplyString(c,"\r\n",2);
 }
 
-void addReplyStatus(redisClient *c, char *status) {
+void addReplyStatus(redisClient *c, const char *status) {
     addReplyStatusLength(c,status,strlen(status));
 }
 
@@ -519,7 +519,7 @@ void addReplyBulk(redisClient *c, robj *obj) {
 }
 
 /* Add a C buffer as bulk reply */
-void addReplyBulkCBuffer(redisClient *c, void *p, size_t len) {
+void addReplyBulkCBuffer(redisClient *c, const void *p, size_t len) {
     addReplyLongLongWithPrefix(c,len,'$');
     addReplyString(c,p,len);
     addReply(c,shared.crlf);
@@ -534,7 +534,7 @@ void addReplyBulkSds(redisClient *c, sds s)  {
 }
 
 /* Add a C nul term string as bulk reply */
-void addReplyBulkCString(redisClient *c, char *s) {
+void addReplyBulkCString(redisClient *c, const char *s) {
     if (s == NULL) {
         addReply(c,shared.nullbulk);
     } else {