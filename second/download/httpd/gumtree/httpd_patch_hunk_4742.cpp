     }
     else {
         st->cache_file = NULL;
     }
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, APLOGNO(01298)
-                 "LDAP cache: Setting shared memory cache file to %s bytes.",
+                 "LDAP cache: Setting shared memory cache file to %s.",
                  st->cache_file);
 
     return NULL;
 }
 
 static const char *util_ldap_set_cache_ttl(cmd_parms *cmd, void *dummy,
