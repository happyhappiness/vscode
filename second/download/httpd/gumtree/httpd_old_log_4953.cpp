ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "Invalid method in request %s - possible attempt to establish SSL connection on non-SSL port", r->the_request);