        sds ci;

        ci = representClusterNodeFlags(sdsempty(), flags);
        serverLog(LL_DEBUG,"GOSSIP %.40s %s:%d %s",
            g->nodename,
            g->ip,
            ntohs(g->port),
            ci);
        sdsfree(ci);

