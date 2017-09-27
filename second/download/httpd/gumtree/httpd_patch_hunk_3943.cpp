                                                          &authnz_ldap_module);
 
     if (sec->secure)
     {
         if (!util_ldap_ssl_supported(s))
         {
-            ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s,
-                     "LDAP: SSL connections (ldaps://) not supported by utilLDAP");
+            ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s, APLOGNO(03159)
+                         "LDAP: SSL connections (ldaps://) not supported by utilLDAP");
             return(!OK);
         }
     }
     */
 
     /* make sure that mod_ldap (util_ldap) is loaded */
