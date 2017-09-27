ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_WARNING, 0, NULL,
                     "macro '%s' multiply defined: "
                     "%s, redefined on line %d of \"%s\"",
                     macro->name, macro->location,
                     cmd->config_file->line_number, cmd->config_file->name);