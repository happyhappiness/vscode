         return err;
     }
 
 #ifdef LDAP_OPT_NETWORK_TIMEOUT
     st->connectionTimeout = atol(ttl);
 
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, APLOGNO(01309)
                  "ldap connection: Setting connection timeout to %ld seconds.",
                  st->connectionTimeout);
 #else
-    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, cmd->server,
+    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, cmd->server, APLOGNO(01310)
                  "LDAP: Connection timeout option not supported by the "
                  "LDAP SDK in use." );
 #endif
 
     return NULL;
 }
