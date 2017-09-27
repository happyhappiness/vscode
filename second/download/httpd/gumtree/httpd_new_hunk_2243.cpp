    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy_balancer_post_request for (%s)", balancer->name);

#endif

    if (worker && worker->s->busy)
        worker->s->busy--;

    return OK;

}

static void recalc_factors(proxy_balancer *balancer)
{
    int i;
    proxy_worker *workers;
