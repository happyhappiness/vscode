static void
statCountersInitSpecial(StatCounters * C)
{
    /*
     * HTTP svc_time hist is kept in milli-seconds; max of 3 hours.
     */
    statHistLogInit(&C->client_http.all_svc_time, 300, 0.0, 3600000.0 * 3.0);
    statHistLogInit(&C->client_http.miss_svc_time, 300, 0.0, 3600000.0 * 3.0);
    statHistLogInit(&C->client_http.nm_svc_time, 300, 0.0, 3600000.0 * 3.0);
    statHistLogInit(&C->client_http.nh_svc_time, 300, 0.0, 3600000.0 * 3.0);
    statHistLogInit(&C->client_http.hit_svc_time, 300, 0.0, 3600000.0 * 3.0);
    /*
     * ICP svc_time hist is kept in micro-seconds; max of 1 minute.
     */
    statHistLogInit(&C->icp.query_svc_time, 300, 0.0, 1000000.0 * 60.0);
    statHistLogInit(&C->icp.reply_svc_time, 300, 0.0, 1000000.0 * 60.0);
    /*
     * DNS svc_time hist is kept in milli-seconds; max of 10 minutes.
     */
    statHistLogInit(&C->dns.svc_time, 300, 0.0, 60000.0 * 10.0);
    /*
     * Cache Digest Stuff
     */
    statHistEnumInit(&C->cd.on_xition_count, CacheDigestHashFuncCount);
    statHistEnumInit(&C->comm_icp_incoming, INCOMING_ICP_MAX);
    statHistEnumInit(&C->comm_dns_incoming, INCOMING_DNS_MAX);
    statHistEnumInit(&C->comm_http_incoming, INCOMING_HTTP_MAX);
    statHistIntInit(&C->select_fds_hist, 256);	/* was SQUID_MAXFD, but it is way too much. It is OK to crop this statistics */
}

/* add special cases here as they arrive */
static void
statCountersClean(StatCounters * C)
{
    assert(C);
    statHistClean(&C->client_http.all_svc_time);
    statHistClean(&C->client_http.miss_svc_time);
    statHistClean(&C->client_http.nm_svc_time);
    statHistClean(&C->client_http.nh_svc_time);
    statHistClean(&C->client_http.hit_svc_time);
    statHistClean(&C->icp.query_svc_time);
    statHistClean(&C->icp.reply_svc_time);
    statHistClean(&C->dns.svc_time);
    statHistClean(&C->cd.on_xition_count);
    statHistClean(&C->comm_icp_incoming);
    statHistClean(&C->comm_dns_incoming);
    statHistClean(&C->comm_http_incoming);
    statHistClean(&C->select_fds_hist);
}

/* add special cases here as they arrive */
static void
statCountersCopy(StatCounters * dest, const StatCounters * orig)
{
    assert(dest && orig);
    /* this should take care of all the fields, but "special" ones */
    xmemcpy(dest, orig, sizeof(*dest));
    /* prepare space where to copy special entries */
    statCountersInitSpecial(dest);
    /* now handle special cases */
    /* note: we assert that histogram capacities do not change */
    statHistCopy(&dest->client_http.all_svc_time, &orig->client_http.all_svc_time);
    statHistCopy(&dest->client_http.miss_svc_time, &orig->client_http.miss_svc_time);
    statHistCopy(&dest->client_http.nm_svc_time, &orig->client_http.nm_svc_time);
    statHistCopy(&dest->client_http.nh_svc_time, &orig->client_http.nh_svc_time);
    statHistCopy(&dest->client_http.hit_svc_time, &orig->client_http.hit_svc_time);
    statHistCopy(&dest->icp.query_svc_time, &orig->icp.query_svc_time);
    statHistCopy(&dest->icp.reply_svc_time, &orig->icp.reply_svc_time);
    statHistCopy(&dest->dns.svc_time, &orig->dns.svc_time);
    statHistCopy(&dest->cd.on_xition_count, &orig->cd.on_xition_count);
    statHistCopy(&dest->comm_icp_incoming, &orig->comm_icp_incoming);
    statHistCopy(&dest->comm_http_incoming, &orig->comm_http_incoming);
    statHistCopy(&dest->select_fds_hist, &orig->select_fds_hist);
}

static void
statCountersHistograms(StoreEntry * sentry)
{
    StatCounters *f = &statCounter;
    storeAppendPrintf(sentry, "client_http.all_svc_time histogram:\n");
    statHistDump(&f->client_http.all_svc_time, sentry, NULL);
    storeAppendPrintf(sentry, "client_http.miss_svc_time histogram:\n");
    statHistDump(&f->client_http.miss_svc_time, sentry, NULL);
    storeAppendPrintf(sentry, "client_http.nm_svc_time histogram:\n");
    statHistDump(&f->client_http.nm_svc_time, sentry, NULL);
    storeAppendPrintf(sentry, "client_http.nh_svc_time histogram:\n");
    statHistDump(&f->client_http.nh_svc_time, sentry, NULL);
    storeAppendPrintf(sentry, "client_http.hit_svc_time histogram:\n");
    statHistDump(&f->client_http.hit_svc_time, sentry, NULL);
    storeAppendPrintf(sentry, "icp.query_svc_time histogram:\n");
    statHistDump(&f->icp.query_svc_time, sentry, NULL);
    storeAppendPrintf(sentry, "icp.reply_svc_time histogram:\n");
    statHistDump(&f->icp.reply_svc_time, sentry, NULL);
    storeAppendPrintf(sentry, "dns.svc_time histogram:\n");
    statHistDump(&f->dns.svc_time, sentry, NULL);
    storeAppendPrintf(sentry, "select_fds_hist histogram:\n");
    statHistDump(&f->select_fds_hist, sentry, NULL);
}

static void
statCountersDump(StoreEntry * sentry)
{
    StatCounters *f = &statCounter;

    struct rusage rusage;
    squid_getrusage(&rusage);
    f->page_faults = rusage_pagefaults(&rusage);
    f->cputime = rusage_cputime(&rusage);

    storeAppendPrintf(sentry, "sample_time = %d.%d (%s)\n",
                      (int) f->timestamp.tv_sec,
                      (int) f->timestamp.tv_usec,
                      mkrfc1123(f->timestamp.tv_sec));
    storeAppendPrintf(sentry, "client_http.requests = %ld\n",
                      (long)f->client_http.requests);
    storeAppendPrintf(sentry, "client_http.hits = %ld\n",
                      (long)f->client_http.hits);
    storeAppendPrintf(sentry, "client_http.errors = %ld\n",
                      (long)f->client_http.errors);
    storeAppendPrintf(sentry, "client_http.kbytes_in = %ld\n",
                      (long)f->client_http.kbytes_in.kb);
    storeAppendPrintf(sentry, "client_http.kbytes_out = %ld\n",
                      (long)f->client_http.kbytes_out.kb);
    storeAppendPrintf(sentry, "client_http.hit_kbytes_out = %ld\n",
                      (long)f->client_http.hit_kbytes_out.kb);

    storeAppendPrintf(sentry, "server.all.requests = %ld\n",
                      (long)f->server.all.requests);
    storeAppendPrintf(sentry, "server.all.errors = %ld\n",
                      (long) f->server.all.errors);
    storeAppendPrintf(sentry, "server.all.kbytes_in = %ld\n",
                      (long) f->server.all.kbytes_in.kb);
    storeAppendPrintf(sentry, "server.all.kbytes_out = %ld\n",
                      (long) f->server.all.kbytes_out.kb);

    storeAppendPrintf(sentry, "server.http.requests = %ld\n",
                      (long) f->server.http.requests);
    storeAppendPrintf(sentry, "server.http.errors = %ld\n",
                      (long) f->server.http.errors);
    storeAppendPrintf(sentry, "server.http.kbytes_in = %ld\n",
                      (long) f->server.http.kbytes_in.kb);
    storeAppendPrintf(sentry, "server.http.kbytes_out = %ld\n",
                      (long) f->server.http.kbytes_out.kb);

    storeAppendPrintf(sentry, "server.ftp.requests = %ld\n",
                      (long) f->server.ftp.requests);
    storeAppendPrintf(sentry, "server.ftp.errors = %ld\n",
                      (long) f->server.ftp.errors);
    storeAppendPrintf(sentry, "server.ftp.kbytes_in = %ld\n",
                      (long) f->server.ftp.kbytes_in.kb);
    storeAppendPrintf(sentry, "server.ftp.kbytes_out = %ld\n",
                      (long) f->server.ftp.kbytes_out.kb);

    storeAppendPrintf(sentry, "server.other.requests = %ld\n",
                      (long) f->server.other.requests);
    storeAppendPrintf(sentry, "server.other.errors = %ld\n",
                      (long) f->server.other.errors);
    storeAppendPrintf(sentry, "server.other.kbytes_in = %ld\n",
                      (long) f->server.other.kbytes_in.kb);
    storeAppendPrintf(sentry, "server.other.kbytes_out = %ld\n",
                      (long) f->server.other.kbytes_out.kb);

    storeAppendPrintf(sentry, "icp.pkts_sent = %ld\n",
                      (long)f->icp.pkts_sent);
    storeAppendPrintf(sentry, "icp.pkts_recv = %ld\n",
                      (long)f->icp.pkts_recv);
    storeAppendPrintf(sentry, "icp.queries_sent = %ld\n",
                      (long)f->icp.queries_sent);
    storeAppendPrintf(sentry, "icp.replies_sent = %ld\n",
                      (long)f->icp.replies_sent);
    storeAppendPrintf(sentry, "icp.queries_recv = %ld\n",
                      (long)f->icp.queries_recv);
    storeAppendPrintf(sentry, "icp.replies_recv = %ld\n",
                      (long)f->icp.replies_recv);
    storeAppendPrintf(sentry, "icp.query_timeouts = %ld\n",
                      (long)f->icp.query_timeouts);
    storeAppendPrintf(sentry, "icp.replies_queued = %ld\n",
                      (long)f->icp.replies_queued);
    storeAppendPrintf(sentry, "icp.kbytes_sent = %ld\n",
                      (long) f->icp.kbytes_sent.kb);
    storeAppendPrintf(sentry, "icp.kbytes_recv = %ld\n",
                      (long) f->icp.kbytes_recv.kb);
    storeAppendPrintf(sentry, "icp.q_kbytes_sent = %ld\n",
                      (long) f->icp.q_kbytes_sent.kb);
    storeAppendPrintf(sentry, "icp.r_kbytes_sent = %ld\n",
                      (long) f->icp.r_kbytes_sent.kb);
    storeAppendPrintf(sentry, "icp.q_kbytes_recv = %ld\n",
                      (long) f->icp.q_kbytes_recv.kb);
    storeAppendPrintf(sentry, "icp.r_kbytes_recv = %ld\n",
                      (long) f->icp.r_kbytes_recv.kb);

#if USE_CACHE_DIGESTS

    storeAppendPrintf(sentry, "icp.times_used = %ld\n",
                      (long)f->icp.times_used);
    storeAppendPrintf(sentry, "cd.times_used = %ld\n",
                      (long)f->cd.times_used);
    storeAppendPrintf(sentry, "cd.msgs_sent = %ld\n",
                      (long)f->cd.msgs_sent);
    storeAppendPrintf(sentry, "cd.msgs_recv = %ld\n",
                      (long)f->cd.msgs_recv);
    storeAppendPrintf(sentry, "cd.memory = %ld\n",
                      (long) f->cd.memory.kb);
    storeAppendPrintf(sentry, "cd.local_memory = %ld\n",
                      (long) (store_digest ? store_digest->mask_size / 1024 : 0));
    storeAppendPrintf(sentry, "cd.kbytes_sent = %ld\n",
                      (long) f->cd.kbytes_sent.kb);
    storeAppendPrintf(sentry, "cd.kbytes_recv = %ld\n",
                      (long) f->cd.kbytes_recv.kb);
#endif

    storeAppendPrintf(sentry, "unlink.requests = %ld\n",
                      (long)f->unlink.requests);
    storeAppendPrintf(sentry, "page_faults = %ld\n",
                      (long)f->page_faults);
    storeAppendPrintf(sentry, "select_loops = %ld\n",
                      (long)f->select_loops);
    storeAppendPrintf(sentry, "cpu_time = %f\n",
                      f->cputime);
    storeAppendPrintf(sentry, "wall_time = %f\n",
                      tvSubDsec(f->timestamp, current_time));
    storeAppendPrintf(sentry, "swap.outs = %ld\n",
                      (long)f->swap.outs);
    storeAppendPrintf(sentry, "swap.ins = %ld\n",
                      (long)f->swap.ins);
    storeAppendPrintf(sentry, "swap.files_cleaned = %ld\n",
                      (long)f->swap.files_cleaned);
    storeAppendPrintf(sentry, "aborted_requests = %ld\n",
                      (long)f->aborted_requests);
}

void
statFreeMemory(void)
{
    int i;

    for (i = 0; i < N_COUNT_HIST; i++)
        statCountersClean(&CountHist[i]);

    for (i = 0; i < N_COUNT_HOUR_HIST; i++)
        statCountersClean(&CountHourHist[i]);
}

static void
statPeerSelect(StoreEntry * sentry)
{
