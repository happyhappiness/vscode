            storeAppendPrintf(sentry, " %s", hashKeyStr(&x->hash));

        storeAppendPrintf(sentry, "\n");

        p = n->peers;

        for (j = 0; j < n->n_peers; j++, p++) {
            storeAppendPrintf(sentry, "    %-22.22s %7.1f %5.1f\n",
                              p->peername,
                              p->rtt,
                              p->hops);
        }
    }
