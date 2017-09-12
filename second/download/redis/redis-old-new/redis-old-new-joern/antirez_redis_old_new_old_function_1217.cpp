static int publishLocationUpdate(const sds zset, const sds member,
                                 const double latitude,
                                 const double longitude) {
    int published;

    /* event is: "<latitude> <longitude>" */
    sds event = sdscatprintf(sdsempty(), "%.7f %.7f", latitude, longitude);
    robj *eventobj = createObject(REDIS_STRING, event);

    /* channel is: __geo:<zset>:<member> */
    /* If you want all events for this zset then just psubscribe
     * to "__geo:<zset>:*" */
    sds chan = sdsnewlen("__geo:", 6);
    chan = sdscatsds(chan, zset);
    chan = sdscatlen(chan, ":", 1);
    chan = sdscatsds(chan, member);
    robj *chanobj = createObject(REDIS_STRING, chan);

    published = pubsubPublishMessage(chanobj, eventobj);

    decrRefCount(chanobj);
    decrRefCount(eventobj);

    return published;
}