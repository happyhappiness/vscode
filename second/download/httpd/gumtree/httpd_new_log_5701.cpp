ap_log_error(APLOG_MARK, APLOG_WARNING, 0, parms->server, APLOGNO(02532)
                             "%s: Protocol '%s' overrides already set parameter(s). "
                             "Check if a +/- prefix is missing.",
                             parms->cmd->name, w);