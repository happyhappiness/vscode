ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(00665)
                     "RewriteCond: NoCase option for non-regex pattern '%s' "
                     "is not supported and will be ignored. (%s:%d)", a2,
                     cmd->directive->filename, cmd->directive->line_num);