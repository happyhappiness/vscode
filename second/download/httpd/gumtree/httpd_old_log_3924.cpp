ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                                 "Copy of SGL failed to obtain shared memory, "
                                 "couldn't update cache");