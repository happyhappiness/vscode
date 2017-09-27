         st->opTimeout->tv_sec = timeout;
     }
     else {
         st->opTimeout = NULL;
     }
 
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, APLOGNO(01313)
                  "ldap connection: Setting op timeout to %ld seconds.",
                  timeout);
 
 #ifndef LDAP_OPT_TIMEOUT
 
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, APLOGNO(01314)
                  "LDAP: LDAP_OPT_TIMEOUT option not supported by the "
                  "LDAP library in use. Using LDAPTimeout value as search "
                  "timeout only." );
 #endif
 
     return NULL;
 }
 
+static const char *util_ldap_set_conn_ttl(cmd_parms *cmd,
+                                            void *dummy,
+                                            const char *val)
+{
+    apr_interval_time_t timeout;
+    util_ldap_state_t *st =
+        (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config,
+                                                  &ldap_module);
+
+    if (ap_timeout_parameter_parse(val, &timeout, "s") != APR_SUCCESS) {
+        return "LDAPConnPoolTTL has wrong format";
+    }
+
+    if (timeout < 0) {
+        /* reserve -1 for default value */
+        timeout =  AP_LDAP_CONNPOOL_INFINITE;
+    }
+    st->connection_pool_ttl = timeout;
+    return NULL;
+}
+static const char *util_ldap_set_retry_delay(cmd_parms *cmd,
+                                            void *dummy,
+                                            const char *val)
+{
+    apr_interval_time_t timeout;
+    util_ldap_state_t *st =
+        (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config,
+                                                  &ldap_module);
+    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
+
+    if (err != NULL) {
+        return err;
+    }
+
+    if (ap_timeout_parameter_parse(val, &timeout, "s") != APR_SUCCESS) {
+        return "LDAPRetryDelay has wrong format";
+    }
+
+    if (timeout < 0) {
+        return "LDAPRetryDelay must be >= 0";
+    }
+
+    st->retry_delay = timeout;
+    return NULL;
+}
+
+static const char *util_ldap_set_retries(cmd_parms *cmd,
+                                            void *dummy,
+                                            const char *val)
+{
+    util_ldap_state_t *st =
+        (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config,
+                                                  &ldap_module);
+    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
 
+    if (err != NULL) {
+        return err;
+    }
+
+    st->retries = atoi(val);
+    if (st->retries < 0) {
+        return  "LDAPRetries must be >= 0";
+    }
+
+    return NULL;
+}
 
 static void *util_ldap_create_config(apr_pool_t *p, server_rec *s)
 {
     util_ldap_state_t *st =
         (util_ldap_state_t *)apr_pcalloc(p, sizeof(util_ldap_state_t));
 
-    /* Create a per vhost pool for mod_ldap to use, serialized with 
+    /* Create a per vhost pool for mod_ldap to use, serialized with
      * st->mutex (also one per vhost).  both are replicated by fork(),
      * no shared memory managed by either.
      */
     apr_pool_create(&st->pool, p);
 #if APR_HAS_THREADS
     apr_thread_mutex_create(&st->mutex, APR_THREAD_MUTEX_DEFAULT, st->pool);
