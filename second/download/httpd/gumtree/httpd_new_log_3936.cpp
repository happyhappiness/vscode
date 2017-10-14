ap_log_error(APLOG_MARK, APLOG_ERR, rv, cmd->server, APLOGNO(01306)
                         "LDAP: Could not open SSL client certificate "
                         "file - %s",
                         cert->path == NULL ? file : cert->path);