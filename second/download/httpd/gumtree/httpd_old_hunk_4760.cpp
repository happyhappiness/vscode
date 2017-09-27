        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01175)
                      "%s: Unlock failed for post_request", balancer->s->name);
    }
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01176)
                  "proxy_balancer_post_request for (%s)", balancer->s->name);

    if (worker && worker->s->busy)
        worker->s->busy--;

    return OK;

}

static void recalc_factors(proxy_balancer *balancer)
{
    int i;
    proxy_worker **workers;
