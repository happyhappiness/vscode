ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, cmd->server, 
                      "LDAP: SSL trusted certificate authority file - %s", 
                       file);