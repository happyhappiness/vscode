ap_log_error(APLOG_MARK, APLOG_DEBUG, 0,
                 cmd->server, "[%" APR_PID_T_FMT "] auth_ldap url parse: `%s', Host: %s, Port: %d, DN: %s, attrib: %s, scope: %s, filter: %s, connection mode: %s",
                 getpid(),
                 url,
                 urld->lud_host,
                 urld->lud_port,
                 urld->lud_dn,
                 urld->lud_attrs? urld->lud_attrs[0] : "(null)",
                 (urld->lud_scope == LDAP_SCOPE_SUBTREE? "subtree" :
                  urld->lud_scope == LDAP_SCOPE_BASE? "base" :
                  urld->lud_scope == LDAP_SCOPE_ONELEVEL? "onelevel" : "unknown"),
                 urld->lud_filter,
                 sec->secure == APR_LDAP_SSL  ? "using SSL": "not using SSL"
                 );