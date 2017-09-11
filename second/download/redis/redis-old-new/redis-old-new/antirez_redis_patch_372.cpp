@@ -242,12 +242,14 @@ typedef long long mstime_t; /* millisecond time type. */
 #define CLIENT_PRE_PSYNC (1<<16)   /* Instance don't understand PSYNC. */
 #define CLIENT_READONLY (1<<17)    /* Cluster client is in read-only state. */
 #define CLIENT_PUBSUB (1<<18)      /* Client is in Pub/Sub mode. */
-#define CLIENT_PREVENT_PROP (1<<19)  /* Don't propagate to AOF / Slaves. */
-#define CLIENT_PENDING_WRITE (1<<20) /* Client has output to send but a write
+#define CLIENT_PREVENT_AOF_PROP (1<<19)  /* Don't propagate to AOF. */
+#define CLIENT_PREVENT_REPL_PROP (1<<20)  /* Don't propagate to slaves. */
+#define CLIENT_PREVENT_PROP (CLIENT_PREVENT_AOF_PROP|CLIENT_PREVENT_REPL_PROP)
+#define CLIENT_PENDING_WRITE (1<<21) /* Client has output to send but a write
                                         handler is yet not installed. */
-#define CLIENT_REPLY_OFF (1<<21)   /* Don't send replies to client. */
-#define CLIENT_REPLY_SKIP_NEXT (1<<22)  /* Set CLIENT_REPLY_SKIP for next cmd */
-#define CLIENT_REPLY_SKIP (1<<23)  /* Don't send just this reply. */
+#define CLIENT_REPLY_OFF (1<<22)   /* Don't send replies to client. */
+#define CLIENT_REPLY_SKIP_NEXT (1<<23)  /* Set CLIENT_REPLY_SKIP for next cmd */
+#define CLIENT_REPLY_SKIP (1<<24)  /* Don't send just this reply. */
 
 /* Client block type (btype field in client structure)
  * if CLIENT_BLOCKED flag is set. */
@@ -1306,6 +1308,8 @@ void propagate(struct redisCommand *cmd, int dbid, robj **argv, int argc, int fl
 void alsoPropagate(struct redisCommand *cmd, int dbid, robj **argv, int argc, int target);
 void forceCommandPropagation(client *c, int flags);
 void preventCommandPropagation(client *c);
+void preventCommandAOF(client *c);
+void preventCommandReplication(client *c);
 int prepareForShutdown();
 #ifdef __GNUC__
 void serverLog(int level, const char *fmt, ...)