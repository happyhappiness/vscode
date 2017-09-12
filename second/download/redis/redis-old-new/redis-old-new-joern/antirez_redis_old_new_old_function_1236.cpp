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