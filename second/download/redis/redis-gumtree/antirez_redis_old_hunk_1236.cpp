        sds ci;

        ci = representRedisNodeFlags(sdsempty(), flags);
        redisLog(REDIS_DEBUG,"GOSSIP %.40s %s:%d %s",
            g->nodename,
            g->ip,
            ntohs(g->port),
