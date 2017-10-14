ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: Processing of request failed backend: %i, "
                     "output: %i", backend_failed, output_failed);