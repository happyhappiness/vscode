ap_log_error(APLOG_MARK, APLOG_ERR, rv, cmd->server, 
                     "LDAP: Could not open SSL trusted certificate authority file - %s", 
                     st->cert_auth_file == NULL ? file : st->cert_auth_file);