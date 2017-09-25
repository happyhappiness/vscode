ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
                             "The %s directive in %s at line %d will probably "
                             "never match because it overlaps an earlier "
                             "%sAlias%s.",
                             cmd->cmd->name, cmd->directive->filename,
                             cmd->directive->line_num,
                             p->handler ? "Script" : "",
                             p->regexp ? "Match" : "");