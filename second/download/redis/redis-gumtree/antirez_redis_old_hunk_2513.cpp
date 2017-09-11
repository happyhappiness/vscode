void freePubsubPattern(void *p);
int listMatchPubsubPattern(void *a, void *b);
int pubsubPublishMessage(robj *channel, robj *message);
void notifyKeyspaceEvent(char *event, robj *key, int dbid);

/* Configuration */
void loadServerConfig(char *filename, char *options);
