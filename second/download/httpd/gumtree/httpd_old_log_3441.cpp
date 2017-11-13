ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, r->server,
                         "cache: updating headers with store_headers failed. "
                         "Removing cached url.");