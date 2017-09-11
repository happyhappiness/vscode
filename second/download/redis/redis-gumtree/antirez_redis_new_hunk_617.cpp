int handleClientsWithPendingWrites(void);
int clientHasPendingReplies(client *c);
void unlinkClient(client *c);
int writeToClient(int fd, client *c, int handler_installed);

#ifdef __GNUC__
void addReplyErrorFormat(client *c, const char *fmt, ...)
