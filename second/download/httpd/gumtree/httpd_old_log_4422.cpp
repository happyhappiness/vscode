ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
                         "Limiting the subrequest depth to a very low level may"
                         " cause normal requests to fail.");