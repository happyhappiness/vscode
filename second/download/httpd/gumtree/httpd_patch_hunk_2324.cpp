     }
     else {
         st->opTimeout = NULL;
     }
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
-                 "[%" APR_PID_T_FMT "] ldap connection: Setting op timeout "
-                 "to %ld seconds.", getpid(), timeout);
+                 "ldap connection: Setting op timeout to %ld seconds.",
+                 timeout);
 
 #ifndef LDAP_OPT_TIMEOUT
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
                  "LDAP: LDAP_OPT_TIMEOUT option not supported by the "
                  "LDAP library in use. Using LDAPTimeout value as search "
