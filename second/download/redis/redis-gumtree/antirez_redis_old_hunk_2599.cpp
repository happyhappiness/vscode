void freePubsubPattern(void *p);
int listMatchPubsubPattern(void *a, void *b);
int pubsubPublishMessage(robj *channel, robj *message);

/* Configuration */
void loadServerConfig(char *filename, char *options);
