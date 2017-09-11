        sds ci;

        ci = representClusterNodeFlags(sdsempty(), flags);
        serverLog(LL_DEBUG,"GOSSIP %.40s %s:%d:%d %s",
            g->nodename,
            g->ip,
            ntohs(g->port),
            ntohs(g->cport),
            ci);
        sdsfree(ci);

