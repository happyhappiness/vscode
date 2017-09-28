 int pubsubUnsubscribeAllChannels(redisClient *c, int notify);
 int pubsubUnsubscribeAllPatterns(redisClient *c, int notify);
 void freePubsubPattern(void *p);
 int listMatchPubsubPattern(void *a, void *b);
 int pubsubPublishMessage(robj *channel, robj *message);
 
+/* Keyspace events notification */
+void notifyKeyspaceEvent(int type, char *event, robj *key, int dbid);
+int keyspaceEventsStringToFlags(char *classes);
+sds keyspaceEventsFlagsToString(int flags);
+
 /* Configuration */
 void loadServerConfig(char *filename, char *options);
 void appendServerSaveParams(time_t seconds, int changes);
 void resetServerSaveParams();
+struct rewriteConfigState; /* Forward declaration to export API. */
+void rewriteConfigRewriteLine(struct rewriteConfigState *state, char *option, sds line, int force);
+int rewriteConfig(char *path);
 
 /* db.c -- Keyspace access API */
 int removeExpire(redisDb *db, robj *key);
 void propagateExpire(redisDb *db, robj *key);
 int expireIfNeeded(redisDb *db, robj *key);
 long long getExpire(redisDb *db, robj *key);
