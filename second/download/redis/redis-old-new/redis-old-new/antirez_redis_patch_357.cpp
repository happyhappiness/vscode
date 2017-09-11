@@ -251,6 +251,7 @@ typedef long long mstime_t; /* millisecond time type. */
 #define CLIENT_REPLY_SKIP_NEXT (1<<23)  /* Set CLIENT_REPLY_SKIP for next cmd */
 #define CLIENT_REPLY_SKIP (1<<24)  /* Don't send just this reply. */
 #define CLIENT_LUA_DEBUG (1<<25)  /* Run EVAL in debug mode. */
+#define CLIENT_LUA_DEBUG_SYNC (1<<26)  /* EVAL debugging without fork() */
 
 /* Client block type (btype field in client structure)
  * if CLIENT_BLOCKED flag is set. */
@@ -1142,6 +1143,7 @@ int processEventsWhileBlocked(void);
 int handleClientsWithPendingWrites(void);
 int clientHasPendingReplies(client *c);
 void unlinkClient(client *c);
+int writeToClient(int fd, client *c, int handler_installed);
 
 #ifdef __GNUC__
 void addReplyErrorFormat(client *c, const char *fmt, ...)