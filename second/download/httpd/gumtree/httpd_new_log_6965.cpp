ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(10032)
                     "Spurious usage of '=' in an environment variable name. "
                     "'%s %s %s' expected instead?", cmd->cmd->name, env, plast);