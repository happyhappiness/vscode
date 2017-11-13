ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(00800)
                 "unable to cache file: %s. Sendfile is not supported on this OS", filename);