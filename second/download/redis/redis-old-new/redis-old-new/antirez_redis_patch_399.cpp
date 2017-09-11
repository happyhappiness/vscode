@@ -1112,6 +1112,7 @@ int clientsArePaused(void);
 int processEventsWhileBlocked(void);
 void handleClientsWithPendingWrites(void);
 int clientHasPendingReplies(client *c);
+void unlinkClient(client *c);
 
 #ifdef __GNUC__
 void addReplyErrorFormat(client *c, const char *fmt, ...)