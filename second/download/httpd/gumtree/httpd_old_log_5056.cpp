ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "redirected from r->uri = %s",
                          top->uri ? top->uri : "(unexpectedly NULL)");