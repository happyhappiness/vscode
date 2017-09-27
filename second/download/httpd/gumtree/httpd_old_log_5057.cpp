ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "subrequested from r->uri = %s",
                          top->uri ? top->uri : "(unexpectedly NULL)");