void
clientdbDump(StoreEntry * sentry)
{
    const char *name;
    ClientInfo *c;
    log_type l;
    int icp_total = 0;
    int icp_hits = 0;
    int http_total = 0;
    int http_hits = 0;
    storeAppendPrintf(sentry, "Cache Clients:\n");
    hash_first(client_table);

    while ((c = (ClientInfo *) hash_next(client_table))) {
        storeAppendPrintf(sentry, "Address: %s\n", hashKeyStr(&c->hash));
        if ( (name = fqdncache_gethostbyaddr(c->addr, 0)) ) {
            storeAppendPrintf(sentry, "Name:    %s\n", name);
        }
        storeAppendPrintf(sentry, "Currently established connections: %d\n",
                          c->n_established);
        storeAppendPrintf(sentry, "    ICP  Requests %d\n",
                          c->Icp.n_requests);

        for (l = LOG_TAG_NONE; l < LOG_TYPE_MAX; ++l) {
            if (c->Icp.result_hist[l] == 0)
                continue;

            icp_total += c->Icp.result_hist[l];

            if (LOG_UDP_HIT == l)
                icp_hits += c->Icp.result_hist[l];

            storeAppendPrintf(sentry, "        %-20.20s %7d %3d%%\n",log_tags[l], c->Icp.result_hist[l], Math::intPercent(c->Icp.result_hist[l], c->Icp.n_requests));
        }

        storeAppendPrintf(sentry, "    HTTP Requests %d\n", c->Http.n_requests);

        for (l = LOG_TAG_NONE; l < LOG_TYPE_MAX; ++l) {
            if (c->Http.result_hist[l] == 0)
                continue;

            http_total += c->Http.result_hist[l];

            if (logTypeIsATcpHit(l))
                http_hits += c->Http.result_hist[l];

            storeAppendPrintf(sentry,
                              "        %-20.20s %7d %3d%%\n",
                              log_tags[l],
                              c->Http.result_hist[l],
                              Math::intPercent(c->Http.result_hist[l], c->Http.n_requests));
        }

        storeAppendPrintf(sentry, "\n");
    }

    storeAppendPrintf(sentry, "TOTALS\n");
    storeAppendPrintf(sentry, "ICP : %d Queries, %d Hits (%3d%%)\n",
                      icp_total, icp_hits, Math::intPercent(icp_hits, icp_total));
    storeAppendPrintf(sentry, "HTTP: %d Requests, %d Hits (%3d%%)\n",
                      http_total, http_hits, Math::intPercent(http_hits, http_total));
}