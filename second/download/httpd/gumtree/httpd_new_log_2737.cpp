ap_log_error(APLOG_MARK, APLOG_WARNING, 0, r->server,
                             "proxy_ftp: could not parse line %s", ctx->buffer);