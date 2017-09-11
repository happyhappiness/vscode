#include "redis.h"

/* This file implements keyspace events notification via Pub/Sub ad
 * described at http://redis.io/topics/keyspace-events.
 *
 * The API provided to the rest of the Redis core is a simple function:
 *
 * notifyKeyspaceEvent(char *event, robj *key, int dbid);
 *
 * 'event' is a C string representing the event name.
 * 'key' is a Redis object representing the key name.
 * 'dbid' is the database ID where the key lives.
 */

void notifyKeyspaceEvent(char *event, robj *key, int dbid) {
    sds keyspace_chan, keyevent_chan;
    int len;
    char buf[24];
    robj *chan1, *chan2, *eventobj;

    if (!server.notify_keyspace_events) return;

    /* The prefix of the two channels is identical if not for
     * 'keyspace' that is 'keyevent' in the event channel name, so
     * we build a single prefix and overwrite 'event' with 'space'. */
    keyspace_chan = sdsnewlen("__keyspace@",11);
    len = ll2string(buf,sizeof(buf),dbid);
    keyspace_chan = sdscatlen(keyspace_chan, buf, len);
    keyspace_chan = sdscatlen(keyspace_chan, "__:", 3);
    keyevent_chan = sdsdup(keyspace_chan); /* Dup the prefix. */
    memcpy(keyevent_chan+5,"event",5); /* Fix it. */

    eventobj = createStringObject(event,strlen(event));

    /* The keyspace channel name has a trailing key name, while
     * the keyevent channel name has a trailing event name. */
    keyspace_chan = sdscatsds(keyspace_chan, key->ptr);
    keyevent_chan = sdscatsds(keyevent_chan, eventobj->ptr);
    chan1 = createObject(REDIS_STRING, keyspace_chan);
    chan2 = createObject(REDIS_STRING, keyevent_chan);

    /* Finally publish the two notifications. */
    pubsubPublishMessage(chan1, eventobj);
    pubsubPublishMessage(chan2, key);

    /* Release objects. */
    decrRefCount(eventobj);
    decrRefCount(chan1);
    decrRefCount(chan2);
}
