     if (!st->util_ldap_cache_lock) return;
 
     sts = apr_global_mutex_child_init(&st->util_ldap_cache_lock,
               apr_global_mutex_lockfile(st->util_ldap_cache_lock), p);
     if (sts != APR_SUCCESS) {
         ap_log_error(APLOG_MARK, APLOG_CRIT, sts, s,
-                     "Failed to initialise global mutex %s in child process %"
-                     APR_PID_T_FMT ".",
-                     ldap_cache_mutex_type, getpid());
+                     "Failed to initialise global mutex %s in child process",
+                     ldap_cache_mutex_type);
     }
 }
 
 static const command_rec util_ldap_cmds[] = {
     AP_INIT_TAKE1("LDAPSharedCacheSize", util_ldap_set_cache_bytes,
                   NULL, RSRC_CONF,
