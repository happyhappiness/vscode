ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                     "proxy: data to read (max %" APR_SIZE_T_FMT
                     " at %" APR_SIZE_T_FMT ")", bufsiz, msg->pos);