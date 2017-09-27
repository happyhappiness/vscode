    }

    if (balancer->failontimeout
        && (apr_table_get(r->notes, "proxy_timedout")) != NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02460)
                      "%s: Forcing worker (%s) into error state "
                      "due to timeout and 'failonstatus' parameter being set",
                       balancer->s->name, ap_proxy_worker_name(r->pool, worker));
        worker->s->status |= PROXY_WORKER_IN_ERROR;
        worker->s->error_time = apr_time_now();

    }

