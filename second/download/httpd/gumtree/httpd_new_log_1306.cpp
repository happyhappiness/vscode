ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                     "No hostname was provided via SNI for a name based"
                     " virtual host");