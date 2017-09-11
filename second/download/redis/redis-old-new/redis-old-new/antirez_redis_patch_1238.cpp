@@ -776,6 +776,7 @@ struct redisServer {
     /* Pubsub */
     dict *pubsub_channels;  /* Map channels to list of subscribed clients */
     list *pubsub_patterns;  /* A list of pubsub_patterns */
+    int notify_keyspace_events; /* Propagate keyspace events via Pub/Sub. */
     /* Cluster */
     int cluster_enabled;    /* Is cluster enabled? */
     clusterState cluster;   /* State of the cluster */
@@ -1134,6 +1135,7 @@ int pubsubUnsubscribeAllPatterns(redisClient *c, int notify);
 void freePubsubPattern(void *p);
 int listMatchPubsubPattern(void *a, void *b);
 int pubsubPublishMessage(robj *channel, robj *message);
+void notifyKeyspaceEvent(char *event, robj *key, int dbid);
 
 /* Configuration */
 void loadServerConfig(char *filename, char *options);