ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
                             APLOGNO(02304) "Discarding directive `%s' not "
                             "allowed in AllowOverrideList at %s:%d",
                             argv[i], cmd->directive->filename,
                             cmd->directive->line_num);