ap_log_error(APLOG_MARK, APLOG_ERR, rv, cmd->server,
                         "LDAP: Could not open SSL trusted certificate "
                         "authority file - %s",
                         cert->path == NULL ? file : cert->path);