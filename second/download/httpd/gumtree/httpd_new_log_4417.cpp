ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(00115)
                     "Useless use of AllowOverrideList in line %d of %s.",
                     cmd->directive->line_num, cmd->directive->filename);