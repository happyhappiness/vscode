ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
                     "Limiting internal redirects to very low numbers may "
                     "cause normal requests to fail.");