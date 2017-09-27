    int access_status;

    access_status = proxy_run_pre_request(worker, balancer, r, conf, url);
    if (access_status == DECLINED && *balancer == NULL) {
        *worker = ap_proxy_get_worker(r->pool, conf, *url);
        if (*worker) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "proxy: %s: found worker %s for %s",
                           (*worker)->scheme, (*worker)->name, *url);

            *balancer = NULL;
            access_status = OK;
        }
        else if (r->proxyreq == PROXYREQ_PROXY) {
            if (conf->forward) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "proxy: *: found forward proxy worker for %s",
                               *url);
                *balancer = NULL;
                *worker = conf->forward;
                access_status = OK;
            }
        }
        else if (r->proxyreq == PROXYREQ_REVERSE) {
            if (conf->reverse) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                              "proxy: *: found reverse proxy worker for %s",
                               *url);
                *balancer = NULL;
                *worker = conf->reverse;
                access_status = OK;
            }
