ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
                             APLOGNO(00116) "Discarding unrecognized "
                             "directive `%s' in AllowOverrideList at %s:%d",
                             argv[i], cmd->directive->filename,
                             cmd->directive->line_num);