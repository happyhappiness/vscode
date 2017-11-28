static double
statPctileSvc(double pctile, int interval, int which)
{
    StatCounters *f;
    StatCounters *l;
    double x;
    assert(interval > 0);

    if (interval > N_COUNT_HIST - 1)
        interval = N_COUNT_HIST - 1;

    f = &CountHist[0];

    l = &CountHist[interval];

    assert(f);

    assert(l);

    switch (which) {

    case PCTILE_HTTP:
        x = statHistDeltaPctile(&l->client_http.all_svc_time, &f->client_http.all_svc_time, pctile);
        break;

    case PCTILE_HIT:
        x = statHistDeltaPctile(&l->client_http.hit_svc_time, &f->client_http.hit_svc_time, pctile);
        break;

    case PCTILE_MISS:
        x = statHistDeltaPctile(&l->client_http.miss_svc_time, &f->client_http.miss_svc_time, pctile);
        break;

    case PCTILE_NM:
        x = statHistDeltaPctile(&l->client_http.nm_svc_time, &f->client_http.nm_svc_time, pctile);
        break;

    case PCTILE_NH:
        x = statHistDeltaPctile(&l->client_http.nh_svc_time, &f->client_http.nh_svc_time, pctile);
        break;

    case PCTILE_ICP_QUERY:
        x = statHistDeltaPctile(&l->icp.query_svc_time, &f->icp.query_svc_time, pctile);
        break;

    case PCTILE_DNS:
        x = statHistDeltaPctile(&l->dns.svc_time, &f->dns.svc_time, pctile);
        break;

    default:
        debugs(49, 5, "statPctileSvc: unknown type.");
        x = 0;
    }

    return x;
}