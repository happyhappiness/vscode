            else if (APR_STATUS_IS_EINTR(rv)) {
                goto worker_pop;
            }
            /* We got some other error. */
            else if (!workers_may_exit) {
                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf,
                             APLOGNO(03099) "ap_queue_pop failed");
            }
            continue;
        }
        if (te != NULL) {
            te->cbfunc(te->baton);

