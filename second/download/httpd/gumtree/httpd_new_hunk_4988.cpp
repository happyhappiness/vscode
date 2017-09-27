                worker->s->error_time = apr_time_now();
                break;
            }
        }
    }

    if (balancer->failontimeout
        && (apr_table_get(r->notes, "proxy_timedout")) != NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02460)
                      "%s: Forcing worker (%s) into error state "
                      "due to timeout and 'failonstatus' parameter being set",
                       balancer->s->name, worker->s->name);
        worker->s->status |= PROXY_WORKER_IN_ERROR;
        worker->s->error_time = apr_time_now();

    }

    if ((rv = PROXY_THREAD_UNLOCK(balancer)) != APR_SUCCESS) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01175)
                      "%s: Unlock failed for post_request", balancer->s->name);
    }
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01176)
                  "proxy_balancer_post_request for (%s)", balancer->s->name);
