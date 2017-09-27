     }
 
 #ifdef LDAP_OPT_NETWORK_TIMEOUT
     st->connectionTimeout = atol(ttl);
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
-                 "[%" APR_PID_T_FMT "] ldap connection: Setting connection timeout to "
-                 "%ld seconds.", getpid(), st->connectionTimeout);
+                 "[%" APR_PID_T_FMT "] ldap connection: Setting connection"
+                 " timeout to %ld seconds.", getpid(), st->connectionTimeout);
 #else
     ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, cmd->server,
-                 "LDAP: Connection timout option not supported by the "
+                 "LDAP: Connection timeout option not supported by the "
                  "LDAP SDK in use." );
 #endif
 
     return NULL;
 }
 
 
+static const char *util_ldap_set_chase_referrals(cmd_parms *cmd,
+                                                 void *config,
+                                                 int mode)
+{
+    util_ldap_config_t *dc =  config;
+
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
+                      "LDAP: Setting referral chasing %s",
+                      (mode == AP_LDAP_CHASEREFERRALS_ON) ? "ON" : "OFF");
+
+    dc->ChaseReferrals = mode;
+
+    return(NULL);
+}
+
+static const char *util_ldap_set_debug_level(cmd_parms *cmd,
+                                             void *config,
+                                             const char *arg) { 
+    util_ldap_state_t *st =
+        (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config,
+                                                  &ldap_module);
+
+    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
+    if (err != NULL) {
+        return err;
+    }
+
+#ifndef AP_LDAP_OPT_DEBUG
+    return "This directive is not supported with the currently linked LDAP library";
+#endif
+
+    st->debug_level = atoi(arg);
+    return NULL;
+} 
+
+static const char *util_ldap_set_referral_hop_limit(cmd_parms *cmd,
+                                                    void *config,
+                                                    const char *hop_limit)
+{
+    util_ldap_config_t *dc =  config;
+
+    dc->ReferralHopLimit = atol(hop_limit);
+
+    if (dc->ReferralHopLimit <= 0) { 
+        return "LDAPReferralHopLimit must be greater than zero (Use 'LDAPReferrals Off' to disable referral chasing)";
+    }
+
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
+                 "LDAP: Limit chased referrals to maximum of %d hops.",
+                 dc->ReferralHopLimit);
+
+    return NULL;
+}
+
+static void *util_ldap_create_dir_config(apr_pool_t *p, char *d) {
+   util_ldap_config_t *dc =
+       (util_ldap_config_t *) apr_pcalloc(p,sizeof(util_ldap_config_t));
+
+   /* defaults are AP_LDAP_CHASEREFERRALS_ON and AP_LDAP_DEFAULT_HOPLIMIT */
+   dc->client_certs = apr_array_make(p, 10, sizeof(apr_ldap_opt_tls_cert_t));
+   dc->ChaseReferrals = AP_LDAP_CHASEREFERRALS_ON;
+   dc->ReferralHopLimit = AP_LDAP_HOPLIMIT_UNSET;
+
+   return dc;
+}
+
+static const char *util_ldap_set_op_timeout(cmd_parms *cmd,
+                                            void *dummy,
+                                            const char *val)
+{
+    long timeout;
+    char *endptr;
+    util_ldap_state_t *st =
+        (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config,
+                                                  &ldap_module);
+    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
+
+    if (err != NULL) {
+        return err;
+    }
+
+    timeout = strtol(val, &endptr, 10);
+    if ((val == endptr) || (*endptr != '\0')) {
+        return "Timeout not numerical";
+    }
+    if (timeout < 0) {
+        return "Timeout must be non-negative";
+    }
+
+    if (timeout) {
+        if (!st->opTimeout) {
+            st->opTimeout = apr_pcalloc(cmd->pool, sizeof(struct timeval));
+        }
+        st->opTimeout->tv_sec = timeout;
+    }
+    else {
+        st->opTimeout = NULL;
+    }
+
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
+                 "[%" APR_PID_T_FMT "] ldap connection: Setting op timeout "
+                 "to %ld seconds.", getpid(), timeout);
+
+#ifndef LDAP_OPT_TIMEOUT
+
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
+                 "LDAP: LDAP_OPT_TIMEOUT option not supported by the "
+                 "LDAP library in use. Using LDAPTimeout value as search "
+                 "timeout only." );
+#endif
+
+    return NULL;
+}
+
+
+
 static void *util_ldap_create_config(apr_pool_t *p, server_rec *s)
 {
     util_ldap_state_t *st =
         (util_ldap_state_t *)apr_pcalloc(p, sizeof(util_ldap_state_t));
 
     /* Create a per vhost pool for mod_ldap to use, serialized with 
-     * st->mutex (also one per vhost) 
+     * st->mutex (also one per vhost).  both are replicated by fork(),
+     * no shared memory managed by either.
      */
     apr_pool_create(&st->pool, p);
 #if APR_HAS_THREADS
     apr_thread_mutex_create(&st->mutex, APR_THREAD_MUTEX_DEFAULT, st->pool);
 #endif
 
