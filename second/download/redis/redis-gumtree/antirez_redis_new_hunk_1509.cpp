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
    link->pc_last_activity = 0;
    /* We set the last_ping_time to "now" even if we actually don't have yet
     * a connection with the node, nor we sent a ping.
     * This is useful to detect a timeout in case we'll not be able to connect
     * with the node at all. */
    link->last_ping_time = mstime();
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
        if (ri) {
            /* TODO: run the callbacks list and rebind. */
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
 * detection and so forth. */
void tryConnectionSharing(sentinelRedisInstance *ri) {
    redisAssert(ri->flags & SRI_SENTINEL);

    /* TODO:
     * 1) Check if there is a match.
     * 2) Free our current link.
     * 3) Reference the other link and increment its reference count. */
    REDIS_NOTUSED(ri);
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
