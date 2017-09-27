ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "Processing of request failed backend: %i, client: %i",
                     backend_failed, client_failed);