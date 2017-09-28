serverLog(LL_DEBUG,"GOSSIP %.40s %s:%d@%d %s",
            g->nodename,
            g->ip,
            ntohs(g->port),
            ntohs(g->cport),
            ci);