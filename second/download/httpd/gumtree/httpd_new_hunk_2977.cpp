                                       proxy_server_conf *conf)
{

    apr_status_t rv;

    if ((rv = PROXY_THREAD_LOCK(balancer)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01173)
                      "%s: Lock failed for post_request",
                      balancer->s->name);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    if (!apr_is_empty_array(balancer->errstatuses)) {
        int i;
        for (i = 0; i < balancer->errstatuses->nelts; i++) {
            int val = ((int *)balancer->errstatuses->elts)[i];
            if (r->status == val) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01174)
                              "%s:  Forcing recovery for worker (%s), "
                              "failonstatus %d",
                              balancer->s->name, worker->s->name, val);
                worker->s->status |= PROXY_WORKER_IN_ERROR;
                worker->s->error_time = apr_time_now();
                break;
            }
        }
    }

    if ((rv = PROXY_THREAD_UNLOCK(balancer)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01175)
                      "%s: Unlock failed for post_request", balancer->s->name);
    }
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01176)
                  "proxy_balancer_post_request for (%s)", balancer->s->name);

    if (worker && worker->s->busy)
        worker->s->busy--;

    return OK;

