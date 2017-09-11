int clientsArePaused(void);
int processEventsWhileBlocked(void);
void handleClientsWithPendingWrites(void);

#ifdef __GNUC__
void addReplyErrorFormat(client *c, const char *fmt, ...)
