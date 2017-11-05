ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                                 "Ignoring flush message received before headers");