ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00959)
                    "ap_proxy_connect_backend disabling worker for (%s) for %"
                    APR_TIME_T_FMT "s",
                    worker->s->hostname, apr_time_sec(worker->s->retry));