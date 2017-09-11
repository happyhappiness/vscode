@@ -142,6 +142,7 @@
                                server.unblocked_clients */
 #define REDIS_LUA_CLIENT 512 /* This is a non connected client used by Lua */
 #define REDIS_ASKING 1024   /* Client issued the ASKING command */
+#define REDIS_CLOSE_ASAP 2048 /* Close this client ASAP */
 
 /* Client request types */
 #define REDIS_REQ_INLINE 1
@@ -152,6 +153,7 @@
 #define REDIS_CLIENT_LIMIT_CLASS_NORMAL 0
 #define REDIS_CLIENT_LIMIT_CLASS_SLAVE 1
 #define REDIS_CLIENT_LIMIT_CLASS_PUBSUB 2
+#define REDIS_CLIENT_LIMIT_NUM_CLASSES 3
 
 /* Slave replication state - slave side */
 #define REDIS_REPL_NONE 0 /* No active replication */
@@ -315,6 +317,7 @@ typedef struct redisClient {
     unsigned long reply_bytes; /* Tot bytes of objects in reply list */
     int sentlen;
     time_t lastinteraction; /* time of the last interaction, used for timeout */
+    time_t obuf_soft_limit_reached_time;
     int flags;              /* REDIS_SLAVE | REDIS_MONITOR | REDIS_MULTI ... */
     int slaveseldb;         /* slave selected db, if this client is a slave */
     int authenticated;      /* when requirepass is non-NULL */
@@ -374,6 +377,12 @@ typedef struct zset {
     zskiplist *zsl;
 } zset;
 
+typedef struct clientBufferLimitsConfig {
+    unsigned long hard_limit_bytes;
+    unsigned long soft_limit_bytes;
+    time_t soft_limit_seconds;
+} clientBufferLimitsConfig;
+
 /*-----------------------------------------------------------------------------
  * Redis cluster data structures
  *----------------------------------------------------------------------------*/
@@ -526,6 +535,7 @@ struct redisServer {
     int sofd;                   /* Unix socket file descriptor */
     int cfd;                    /* Cluster bus lisetning socket */
     list *clients;              /* List of active clients */
+    list *clients_to_close;     /* Clients to close asynchronously */
     list *slaves, *monitors;    /* List of slaves and MONITORs */
     redisClient *current_client; /* Current client, only used on crash report */
     char neterr[ANET_ERR_LEN];  /* Error buffer for anet.c */
@@ -559,6 +569,7 @@ struct redisServer {
     size_t client_max_querybuf_len; /* Limit for client query buffer length */
     int dbnum;                      /* Total number of configured DBs */
     int daemonize;                  /* True if running as a daemon */
+    clientBufferLimitsConfig client_obuf_limits[REDIS_CLIENT_LIMIT_NUM_CLASSES];
     /* AOF persistence */
     int aof_state;                  /* REDIS_AOF_(ON|OFF|WAIT_REWRITE) */
     int aof_fsync;                  /* Kind of fsync() policy */
@@ -792,6 +803,8 @@ sds getAllClientsInfoString(void);
 void rewriteClientCommandVector(redisClient *c, int argc, ...);
 void rewriteClientCommandArgument(redisClient *c, int i, robj *newval);
 unsigned long getClientOutputBufferMemoryUsage(redisClient *c);
+void freeClientsInAsyncFreeQueue(void);
+int asyncCloseClientOnOutputBufferLimitReached(redisClient *c);
 
 #ifdef __GNUC__
 void addReplyErrorFormat(redisClient *c, const char *fmt, ...)