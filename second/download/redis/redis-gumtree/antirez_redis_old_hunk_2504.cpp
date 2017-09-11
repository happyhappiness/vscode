 * 'dbid' is the database ID where the key lives.  */
void notifyKeyspaceEvent(int type, char *event, robj *key, int dbid) {
    sds chan;
    robj *chanobj;
    int len = -1;
    char buf[24];

    /* If notifications for this class of events are off, return ASAP. */
    if (!(server.notify_keyspace_events & type)) return;

    /* __keyspace@<db>__:<key> <event> notifications. */
    if (server.notify_keyspace_events & REDIS_NOTIFY_KEYSPACE) {
        robj *eventobj;

        chan = sdsnewlen("__keyspace@",11);
        len = ll2string(buf,sizeof(buf),dbid);
        chan = sdscatlen(chan, buf, len);
        chan = sdscatlen(chan, "__:", 3);
        eventobj = createStringObject(event,strlen(event));
        chanobj = createObject(REDIS_STRING, chan);
        pubsubPublishMessage(chanobj, eventobj);
        decrRefCount(chanobj);
