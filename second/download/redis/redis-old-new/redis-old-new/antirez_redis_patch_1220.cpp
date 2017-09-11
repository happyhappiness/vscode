@@ -291,6 +291,20 @@
 #define REDIS_PROPAGATE_AOF 1
 #define REDIS_PROPAGATE_REPL 2
 
+/* Keyspace changes notification classes. Every class is associated with a
+ * character for configuration purposes. */
+#define REDIS_NOTIFY_KEYSPACE (1<<0)    /* K */
+#define REDIS_NOTIFY_KEYEVENT (1<<1)    /* E */
+#define REDIS_NOTIFY_GENERIC (1<<2)     /* g */
+#define REDIS_NOTIFY_STRING (1<<3)      /* $ */
+#define REDIS_NOTIFY_LIST (1<<4)        /* l */
+#define REDIS_NOTIFY_SET (1<<5)         /* s */
+#define REDIS_NOTIFY_HASH (1<<6)        /* h */
+#define REDIS_NOTIFY_ZSET (1<<7)        /* z */
+#define REDIS_NOTIFY_EXPIRED (1<<8)     /* x */
+#define REDIS_NOTIFY_EVICTED (1<<9)     /* e */
+#define REDIS_NOTIFY_ALL (REDIS_NOTIFY_GENERIC | REDIS_NOTIFY_STRING | REDIS_NOTIFY_LIST | REDIS_NOTIFY_SET | REDIS_NOTIFY_HASH | REDIS_NOTIFY_ZSET | REDIS_NOTIFY_EXPIRED | REDIS_NOTIFY_EVICTED)      /* A */
+
 /* Using the following macro you can run code inside serverCron() with the
  * specified period, specified in milliseconds.
  * The actual resolution depends on server.hz. */
@@ -776,7 +790,8 @@ struct redisServer {
     /* Pubsub */
     dict *pubsub_channels;  /* Map channels to list of subscribed clients */
     list *pubsub_patterns;  /* A list of pubsub_patterns */
-    int notify_keyspace_events; /* Propagate keyspace events via Pub/Sub. */
+    int notify_keyspace_events; /* Events to propagate via Pub/Sub. This is an
+                                   xor of REDIS_NOTIFY... flags. */
     /* Cluster */
     int cluster_enabled;    /* Is cluster enabled? */
     clusterState cluster;   /* State of the cluster */
@@ -1136,7 +1151,11 @@ int pubsubUnsubscribeAllPatterns(redisClient *c, int notify);
 void freePubsubPattern(void *p);
 int listMatchPubsubPattern(void *a, void *b);
 int pubsubPublishMessage(robj *channel, robj *message);
-void notifyKeyspaceEvent(char *event, robj *key, int dbid);
+
+/* Keyspace events notification */
+void notifyKeyspaceEvent(int type, char *event, robj *key, int dbid);
+int keyspaceEventsStringToFlags(char *classes);
+sds keyspaceEventsFlagsToString(int flags);
 
 /* Configuration */
 void loadServerConfig(char *filename, char *options);