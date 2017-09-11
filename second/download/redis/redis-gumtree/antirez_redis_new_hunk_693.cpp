int clientsArePaused(void);
int processEventsWhileBlocked(void);
void handleClientsWithPendingWrites(void);
int clientHasPendingReplies(client *c);

#ifdef __GNUC__
void addReplyErrorFormat(client *c, const char *fmt, ...)
