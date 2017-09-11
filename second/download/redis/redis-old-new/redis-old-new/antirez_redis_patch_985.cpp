@@ -623,6 +623,8 @@ struct redisServer {
     list *clients_to_close;     /* Clients to close asynchronously */
     list *slaves, *monitors;    /* List of slaves and MONITORs */
     redisClient *current_client; /* Current client, only used on crash report */
+    int clients_paused;         /* True if clients are currently paused */
+    mstime_t clients_pause_end_time; /* Time when we undo clients_paused */
     char neterr[ANET_ERR_LEN];   /* Error buffer for anet.c */
     dict *migrate_cached_sockets;/* MIGRATE cached sockets */
     /* RDB / AOF loading information */
@@ -972,6 +974,8 @@ char *getClientLimitClassName(int class);
 void flushSlavesOutputBuffers(void);
 void disconnectSlaves(void);
 int listenToPort(int port, int *fds, int *count);
+void pauseClients(mstime_t duration);
+int clientsArePaused(void);
 
 #ifdef __GNUC__
 void addReplyErrorFormat(redisClient *c, const char *fmt, ...)