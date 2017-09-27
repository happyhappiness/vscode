    }

    return APR_SUCCESS;
}
#endif

/*
 * ap_proxy_initialize_worker_share() concerns itself
 * with initializing those parts of worker which
 * are, or could be, shared. Basically worker->s
 */
PROXY_DECLARE(void) ap_proxy_initialize_worker_share(proxy_server_conf *conf,
                                                     proxy_worker *worker,
                                                     server_rec *s)
{
    proxy_worker_stat *score = NULL;

    if (PROXY_WORKER_IS_INITIALIZED(worker)) {
        /* The worker share is already initialized */
        ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, s,
                     "proxy: worker %s already initialized",
                     worker->name);
        return;
    }
    if (!worker->s) {
        /* Get scoreboard slot */
        if (ap_scoreboard_image) {
            score = (proxy_worker_stat *) ap_get_scoreboard_lb(worker->id);
            if (!score) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                      "proxy: ap_get_scoreboard_lb(%d) failed in child %" APR_PID_T_FMT " for worker %s",
                      worker->id, getpid(), worker->name);
            }
            else {
                 ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, s,
                      "proxy: grabbed scoreboard slot %d in child %" APR_PID_T_FMT " for worker %s",
                      worker->id, getpid(), worker->name);
            }
        }
        if (!score) {
            score = (proxy_worker_stat *) apr_pcalloc(conf->pool, sizeof(proxy_worker_stat));
            ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, s,
                  "proxy: initialized plain memory in child %" APR_PID_T_FMT " for worker %s",
                  getpid(), worker->name);
        }
        worker->s = score;
        /*
         * recheck to see if we've already been here. Possible
         * if proxy is using scoreboard to hold shared stats
         */
        if (PROXY_WORKER_IS_INITIALIZED(worker)) {
            /* The worker share is already initialized */
            ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, s,
                         "proxy: worker %s already initialized",
                         worker->name);
            return;
        }
    }
    if (worker->route) {
        strcpy(worker->s->route, worker->route);
    }
    else {
        *worker->s->route = '\0';
