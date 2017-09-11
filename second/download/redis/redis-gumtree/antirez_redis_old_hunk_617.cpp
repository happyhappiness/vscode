int handleClientsWithPendingWrites(void);
int clientHasPendingReplies(client *c);
void unlinkClient(client *c);

#ifdef __GNUC__
void addReplyErrorFormat(client *c, const char *fmt, ...)
