        state, from->ip, fromport, to->ip, toport, NULL);
}

/* =============================== instanceLink ============================= */

/* Create a not yet connected link object. */
instanceLink *createInstanceLink(void) {
    instanceLink *link = zmalloc(sizeof(*link));

    link->refcount = 1;
    link->disconnected = 1;
    link->pending_commands = 0;
    link->cc = NULL;
    link->pc = NULL;
    link->cc_conn_time = 0;
    link->pc_conn_time = 0;
    link->last_reconn_time = 0;
    link->pc_last_activity = 0;
    /* We set the act_ping_time to "now" even if we actually don't have yet
     * a connection with the node, nor we sent a ping.
     * This is useful to detect a timeout in case we'll not be able to connect
     * with the node at all. */
    link->act_ping_time = mstime();
    link->last_ping_time = 0;
    link->last_avail_time = mstime();
    link->last_pong_time = mstime();
    return link;
}

/* Disconnect an hiredis connection in the context of an instance link. */
void instanceLinkCloseConnection(instanceLink *link, redisAsyncContext *c) {
    if (c == NULL) return;

    if (link->cc == c) {
        link->cc = NULL;
        link->pending_commands = 0;
    }
    if (link->pc == c) link->pc = NULL;
    c->data = NULL;
    link->disconnected = 1;
    redisAsyncFree(c);
}

/* Decrement the refcount of a link object, if it drops to zero, actually
 * free it and return NULL. Otherwise don't do anything and return the pointer
 * to the object.
 *
 * If we are not going to free the link and ri is not NULL, we rebind all the
 * pending requests in link->cc (hiredis connection for commands) to a
 * callback that will just ignore them. This is useful to avoid processing
 * replies for an instance that no longer exists. */
instanceLink *releaseInstanceLink(instanceLink *link, sentinelRedisInstance *ri)
{
    redisAssert(link->refcount > 0);
    link->refcount--;
    if (link->refcount != 0) {
        if (ri && ri->link->cc) {
            /* This instance may have pending callbacks in the hiredis async
             * context, having as 'privdata' the instance that we are going to
             * free. Let's rewrite the callback list, directly exploiting
             * hiredis internal data structures, in order to bind them with
             * a callback that will ignore the reply at all. */
            redisCallback *cb;
            redisCallbackList *callbacks = &link->cc->replies;

            cb = callbacks->head;
            while(cb) {
                if (cb->privdata == ri) {
                    cb->fn = sentinelDiscardReplyCallback;
                    cb->privdata = NULL; /* Not strictly needed. */
                }
                cb = cb->next;
            }
        }
        return link; /* Other active users. */
    }

    instanceLinkCloseConnection(link,link->cc);
    instanceLinkCloseConnection(link,link->pc);
    zfree(link);
    return NULL;
}

/* This function will attempt to share the instance link we already have
 * for the same Sentinel in the context of a different master, with the
 * instance we are passing as argument.
 *
 * This way multiple Sentinel objects that refer all to the same physical
 * Sentinel instance but in the context of different masters will use
 * a single connection, will send a single PING per second for failure
 * detection and so forth.
 *
 * Return REDIS_OK if a matching Sentinel was found in the context of a
 * different master and sharing was performed. Otherwise REDIS_ERR
 * is returned. */
int sentinelTryConnectionSharing(sentinelRedisInstance *ri) {
    redisAssert(ri->flags & SRI_SENTINEL);
    dictIterator *di;
    dictEntry *de;

    if (ri->runid == NULL) return REDIS_ERR; /* No way to identify it. */
    if (ri->link->refcount > 1) return REDIS_ERR; /* Already shared. */

    di = dictGetIterator(sentinel.masters);
    while((de = dictNext(di)) != NULL) {
        sentinelRedisInstance *master = dictGetVal(de), *match;
        /* We want to share with the same physical Sentinel referenced
         * in other masters, so skip our master. */
        if (master == ri->master) continue;
        match = getSentinelRedisInstanceByAddrAndRunID(master->sentinels,
                                                       NULL,0,ri->runid);
        if (match == ri) continue; /* Should never happen but... safer. */

        /* We identified a matching Sentinel, great! Let's free our link
         * and use the one of the matching Sentinel. */
        releaseInstanceLink(ri->link,NULL);
        ri->link = match->link;
        match->link->refcount++;
        return REDIS_OK;
    }
    dictReleaseIterator(di);
    return REDIS_ERR;
}

/* When we detect a Sentinel to switch address (reporting a different IP/port
 * pair in Hello messages), let's update all the matching Sentinels in the
 * context of other masters as well and disconnect the links, so that everybody
 * will be updated.
 *
 * Return the number of updated Sentinel addresses. */
int sentinelUpdateSentinelAddressInAllMasters(sentinelRedisInstance *ri) {
    redisAssert(ri->flags & SRI_SENTINEL);
    dictIterator *di;
    dictEntry *de;
    int reconfigured = 0;

    di = dictGetIterator(sentinel.masters);
    while((de = dictNext(di)) != NULL) {
        sentinelRedisInstance *master = dictGetVal(de), *match;
        match = getSentinelRedisInstanceByAddrAndRunID(master->sentinels,
                                                       NULL,0,ri->runid);
        if (match->link->disconnected == 0) {
            instanceLinkCloseConnection(match->link,match->link->cc);
            instanceLinkCloseConnection(match->link,match->link->pc);
        }
        if (match == ri) continue; /* Address already updated for it. */
        /* Update the address of the matching Sentinel by copying the address
         * of the Sentinel object that received the address update. */
        releaseSentinelAddr(match->addr);
        match->addr = dupSentinelAddr(ri->addr);
        reconfigured++;
    }
    dictReleaseIterator(di);
    if (reconfigured)
        sentinelEvent(REDIS_NOTICE,"+sentinel-address-update", ri,
                    "%@ %d additional matching instances", reconfigured);
    return reconfigured;
}

/* This function is called when an hiredis connection reported an error.
 * We set it to NULL and mark the link as disconnected so that it will be
 * reconnected again.
 *
 * Note: we don't free the hiredis context as hiredis will do it for us
 * for async connections. */
void instanceLinkConnectionError(const redisAsyncContext *c) {
    instanceLink *link = c->data;
    int pubsub;

    if (!link) return;

    pubsub = (link->pc == c);
    if (pubsub)
        link->pc = NULL;
    else
        link->cc = NULL;
    link->disconnected = 1;
}

/* Hiredis connection established / disconnected callbacks. We need them
 * just to cleanup our link state. */
void sentinelLinkEstablishedCallback(const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) instanceLinkConnectionError(c);
}

void sentinelDisconnectCallback(const redisAsyncContext *c, int status) {
    REDIS_NOTUSED(status);
    instanceLinkConnectionError(c);
}

/* ========================== sentinelRedisInstance ========================= */

/* Create a redis instance, the following fields must be populated by the
