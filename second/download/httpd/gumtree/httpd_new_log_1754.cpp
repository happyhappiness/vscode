ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Handler for %s returned invalid result code %d",
                          r->handler, result);