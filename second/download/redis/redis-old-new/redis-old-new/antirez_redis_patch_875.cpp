@@ -1006,6 +1006,7 @@ void disconnectSlaves(void);
 int listenToPort(int port, int *fds, int *count);
 void pauseClients(mstime_t duration);
 int clientsArePaused(void);
+int processEventsWhileBlocked(void);
 
 #ifdef __GNUC__
 void addReplyErrorFormat(redisClient *c, const char *fmt, ...)