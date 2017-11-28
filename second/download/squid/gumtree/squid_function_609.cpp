static void
statCountersHistograms(StoreEntry * sentry)
{
    storeAppendPrintf(sentry, "client_http.allSvcTime histogram:\n");
    statCounter.client_http.allSvcTime.dump(sentry, NULL);
    storeAppendPrintf(sentry, "client_http.missSvcTime histogram:\n");
    statCounter.client_http.missSvcTime.dump(sentry, NULL);
    storeAppendPrintf(sentry, "client_http.nearMissSvcTime histogram:\n");
    statCounter.client_http.nearMissSvcTime.dump(sentry, NULL);
    storeAppendPrintf(sentry, "client_http.nearHitSvcTime histogram:\n");
    statCounter.client_http.nearHitSvcTime.dump(sentry, NULL);
    storeAppendPrintf(sentry, "client_http.hitSvcTime histogram:\n");
    statCounter.client_http.hitSvcTime.dump(sentry, NULL);
    storeAppendPrintf(sentry, "icp.querySvcTime histogram:\n");
    statCounter.icp.querySvcTime.dump(sentry, NULL);
    storeAppendPrintf(sentry, "icp.replySvcTime histogram:\n");
    statCounter.icp.replySvcTime.dump(sentry, NULL);
    storeAppendPrintf(sentry, "dns.svc_time histogram:\n");
    statCounter.dns.svcTime.dump(sentry, NULL);
    storeAppendPrintf(sentry, "select_fds_hist histogram:\n");
    statCounter.select_fds_hist.dump(sentry, NULL);
}