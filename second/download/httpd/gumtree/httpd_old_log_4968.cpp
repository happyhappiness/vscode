ap_log_error(APLOG_MARK, APLOG_ERR, rv, c->base_server,
                     "core_filter: sendfile_nonblocking: "
                     "this should never happen");