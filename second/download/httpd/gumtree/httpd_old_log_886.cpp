ap_log_error(APLOG_MARK, APLOG_INFO, outctx->rc, c->base_server,
                     "failed to write %d of %d bytes (%s)",
                     len - (apr_size_t)res, len, reason);