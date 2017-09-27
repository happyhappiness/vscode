ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, cmd->server, APLOGNO(00113)
                     "%s:%d cannot use a full URL in a 401 ErrorDocument "
                     "directive --- ignoring!", cmd->directive->filename, cmd->directive->line_num);