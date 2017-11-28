    if (p->login)
        storeAppendPrintf(sentry, " login=%s", p->login);

    if (p->mcast.ttl > 0)
        storeAppendPrintf(sentry, " ttl=%d", p->mcast.ttl);

    if (p->connect_timeout_raw > 0)
        storeAppendPrintf(sentry, " connect-timeout=%d", (int)p->connect_timeout_raw);

    if (p->connect_fail_limit != PEER_TCP_MAGIC_COUNT)
        storeAppendPrintf(sentry, " connect-fail-limit=%d", p->connect_fail_limit);

#if USE_CACHE_DIGESTS

