 static const char *util_ldap_set_chase_referrals(cmd_parms *cmd,
                                                  void *config,
                                                  int mode)
 {
     util_ldap_config_t *dc =  config;
 
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, APLOGNO(01311)
                       "LDAP: Setting referral chasing %s",
                       (mode == AP_LDAP_CHASEREFERRALS_ON) ? "ON" : "OFF");
 
     dc->ChaseReferrals = mode;
 
     return(NULL);
 }
 
 static const char *util_ldap_set_debug_level(cmd_parms *cmd,
                                              void *config,
-                                             const char *arg) { 
+                                             const char *arg) {
+#ifdef AP_LDAP_OPT_DEBUG
     util_ldap_state_t *st =
         (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config,
                                                   &ldap_module);
+#endif
 
     const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
     if (err != NULL) {
         return err;
     }
 
 #ifndef AP_LDAP_OPT_DEBUG
     return "This directive is not supported with the currently linked LDAP library";
-#endif
-
+#else
     st->debug_level = atoi(arg);
     return NULL;
-} 
+#endif
+}
 
 static const char *util_ldap_set_referral_hop_limit(cmd_parms *cmd,
                                                     void *config,
                                                     const char *hop_limit)
 {
     util_ldap_config_t *dc =  config;
 
     dc->ReferralHopLimit = atol(hop_limit);
 
-    if (dc->ReferralHopLimit <= 0) { 
+    if (dc->ReferralHopLimit <= 0) {
         return "LDAPReferralHopLimit must be greater than zero (Use 'LDAPReferrals Off' to disable referral chasing)";
     }
 
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, APLOGNO(01312)
                  "LDAP: Limit chased referrals to maximum of %d hops.",
                  dc->ReferralHopLimit);
 
     return NULL;
 }
 
