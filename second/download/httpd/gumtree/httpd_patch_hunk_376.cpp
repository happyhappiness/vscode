         (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config, 
 						  &ldap_module);
 
     st->cache_bytes = atol(bytes);
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0, cmd->server, 
-                      "[%d] ldap cache: Setting shared memory cache size to %d bytes.", 
-                      getpid(), st->cache_bytes);
+                 "[%" APR_PID_T_FMT "] ldap cache: Setting shared memory "
+                 " cache size to %" APR_SIZE_T_FMT " bytes.", 
+                 getpid(), st->cache_bytes);
 
     return NULL;
 }
 
 static const char *util_ldap_set_cache_file(cmd_parms *cmd, void *dummy, const char *file)
 {
