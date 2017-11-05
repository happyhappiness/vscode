ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(00114)
                     "Useless use of AllowOverride in line %d of %s.",
                     cmd->directive->line_num, cmd->directive->filename);