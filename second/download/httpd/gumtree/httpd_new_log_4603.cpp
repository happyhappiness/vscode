ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00866)
                      "failed to make connection to backend: %s:%u",
                      backend->hostname, backend->port);