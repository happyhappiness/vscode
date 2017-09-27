                worker->s->error_time = apr_time_now();
                break;
            }
        }
    }

    if (balancer->failontimeout
        && (apr_table_get(r->notes, "proxy_timedout")) != NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "%s: Forcing worker (%s) into error state "
                      "due to timeout and 'failonstatus' parameter being set",
                       balancer->name, worker->name);
        worker->s->status |= PROXY_WORKER_IN_ERROR;
        worker->s->error_time = apr_time_now();

    }

    if ((rv = PROXY_THREAD_UNLOCK(balancer)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
            "proxy: BALANCER: (%s). Unlock failed for post_request",
            balancer->name);
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
