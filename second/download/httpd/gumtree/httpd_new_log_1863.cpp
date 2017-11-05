ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
              "Ignoring deprecated use of DefaultType in line %d of %s.",
                     cmd->directive->line_num, cmd->directive->filename);