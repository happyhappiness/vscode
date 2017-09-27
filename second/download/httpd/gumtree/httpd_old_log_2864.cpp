ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
                     "Useless use of AllowOverride in line %d.",
                     cmd->directive->line_num);