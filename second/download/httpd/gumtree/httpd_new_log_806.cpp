ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
                     "RewriteCond: NoCase option for non-regex pattern '%s' "
                     "is not supported and will be ignored.", a2);