     return NULL;
 }
 
 
 static const char *util_ldap_set_chase_referrals(cmd_parms *cmd,
                                                  void *config,
-                                                 int mode)
+                                                 const char *arg)
 {
     util_ldap_config_t *dc =  config;
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, APLOGNO(01311)
-                      "LDAP: Setting referral chasing %s",
-                      (mode == AP_LDAP_CHASEREFERRALS_ON) ? "ON" : "OFF");
+                      "LDAP: Setting referral chasing %s", arg);
 
-    dc->ChaseReferrals = mode;
+    if (0 == strcasecmp(arg, "on")) {
+        dc->ChaseReferrals = AP_LDAP_CHASEREFERRALS_ON;
+    }
+    else if (0 == strcasecmp(arg, "off")) {
+        dc->ChaseReferrals = AP_LDAP_CHASEREFERRALS_OFF;
+    }
+    else if (0 == strcasecmp(arg, "default")) {
+        dc->ChaseReferrals = AP_LDAP_CHASEREFERRALS_SDKDEFAULT;
+    }
+    else {
+        return "LDAPReferrals must be 'on', 'off', or 'default'";
+    }
 
     return(NULL);
 }
 
 static const char *util_ldap_set_debug_level(cmd_parms *cmd,
                                              void *config,
