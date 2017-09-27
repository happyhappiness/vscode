ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                     "Invalid URI in request %s", r->the_request);