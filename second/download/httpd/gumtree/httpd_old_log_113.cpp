ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server,
                "failed to write %d of %d bytes (%s)",
                n > 0 ? len - n : len, len, reason);