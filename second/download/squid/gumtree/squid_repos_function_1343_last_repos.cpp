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
        x = statHistDeltaPctile(l->client_http.allSvcTime,f->client_http.allSvcTime, pctile);
        break;

    case PCTILE_HIT:
        x = statHistDeltaPctile(l->client_http.hitSvcTime,f->client_http.hitSvcTime, pctile);
        break;

    case PCTILE_MISS:
        x = statHistDeltaPctile(l->client_http.missSvcTime,f->client_http.missSvcTime, pctile);
        break;

    case PCTILE_NM:
        x = statHistDeltaPctile(l->client_http.nearMissSvcTime,f->client_http.nearMissSvcTime, pctile);
        break;

    case PCTILE_NH:
        x = statHistDeltaPctile(l->client_http.nearHitSvcTime,f->client_http.nearHitSvcTime, pctile);
        break;

    case PCTILE_ICP_QUERY:
        x = statHistDeltaPctile(l->icp.querySvcTime,f->icp.querySvcTime, pctile);
        break;

    case PCTILE_DNS:
        x = statHistDeltaPctile(l->dns.svcTime,f->dns.svcTime, pctile);
        break;

    default:
        debugs(49, 5, "statPctileSvc: unknown type.");
        x = 0;
    }

    return x;
}