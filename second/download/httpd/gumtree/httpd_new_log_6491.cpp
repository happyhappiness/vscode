ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(00115)
                     "Useless use of AllowOverrideList at %s:%d",
                     cmd->directive->filename, cmd->directive->line_num);