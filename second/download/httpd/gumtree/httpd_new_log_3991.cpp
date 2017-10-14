ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(00671)
                             "The %s directive in %s at line %d will probably "
                             "never match because it overlaps an earlier "
                             "%sAlias%s.",
                             cmd->cmd->name, cmd->directive->filename,
                             cmd->directive->line_num,
                             alias->handler ? "Script" : "",
                             alias->regexp ? "Match" : "");