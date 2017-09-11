@@ -305,6 +305,7 @@ typedef struct redisClient {
     int multibulklen;       /* number of multi bulk arguments left to read */
     long bulklen;           /* length of bulk argument in multi bulk request */
     list *reply;
+    unsigned long reply_bytes; /* Tot bytes of objects in reply list */
     int sentlen;
     time_t lastinteraction; /* time of the last interaction, used for timeout */
     int flags;              /* REDIS_SLAVE | REDIS_MONITOR | REDIS_MULTI ... */
@@ -783,6 +784,7 @@ sds getClientInfoString(redisClient *client);
 sds getAllClientsInfoString(void);
 void rewriteClientCommandVector(redisClient *c, int argc, ...);
 void rewriteClientCommandArgument(redisClient *c, int i, robj *newval);
+unsigned long getClientOutputBufferMemoryUsage(redisClient *c);
 
 #ifdef __GNUC__
 void addReplyErrorFormat(redisClient *c, const char *fmt, ...)