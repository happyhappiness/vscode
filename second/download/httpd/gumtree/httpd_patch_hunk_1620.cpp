 static const char *util_ldap_set_trusted_client_cert(cmd_parms *cmd,
                                                      void *config,
                                                      const char *type,
                                                      const char *file,
                                                      const char *password)
 {
-    util_ldap_state_t *st =
-        (util_ldap_state_t *)ap_get_module_config(cmd->server->module_config,
-                                                  &ldap_module);
+    util_ldap_config_t *dc =  config;
     apr_finfo_t finfo;
     apr_status_t rv;
     int cert_type = 0;
     apr_ldap_opt_tls_cert_t *cert;
 
     /* handle the certificate type */
     if (type) {
         cert_type = util_ldap_parse_cert_type(type);
         if (APR_LDAP_CA_TYPE_UNKNOWN == cert_type) {
             return apr_psprintf(cmd->pool, "The certificate type \"%s\" is "
                                            "not recognised. It should be one "
-                                           "of CERT_DER, CERT_BASE64, "
-                                           "CERT_NICKNAME, CERT_PFX,"
+                                           "of CA_DER, CA_BASE64, "
+                                           "CERT_DER, CERT_BASE64, "
+                                           "CERT_NICKNAME, CERT_PFX, "
                                            "KEY_DER, KEY_BASE64, KEY_PFX",
                                            type);
         }
-        else if (APR_LDAP_CA_TYPE_DER == cert_type ||
-                 APR_LDAP_CA_TYPE_BASE64 == cert_type ||
-                 APR_LDAP_CA_TYPE_CERT7_DB == cert_type ||
+        else if ( APR_LDAP_CA_TYPE_CERT7_DB == cert_type ||
                  APR_LDAP_CA_TYPE_SECMOD == cert_type ||
                  APR_LDAP_CERT_TYPE_PFX == cert_type ||
                  APR_LDAP_CERT_TYPE_KEY3_DB == cert_type) {
             return apr_psprintf(cmd->pool, "The certificate type \"%s\" is "
                                            "only valid within a "
                                            "LDAPTrustedGlobalCert directive. "
-                                           "Only CERT_DER, CERT_BASE64, "
+                                           "Only CA_DER, CA_BASE64, "
+                                           "CERT_DER, CERT_BASE64, "
                                            "CERT_NICKNAME, KEY_DER, and "
                                            "KEY_BASE64 may be used.", type);
         }
     }
     else {
         return "Certificate type was not specified.";
     }
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
                       "LDAP: SSL trusted client cert - %s (type %s)",
                        file, type);
 
-    /* add the certificate to the global array */
-    cert = (apr_ldap_opt_tls_cert_t *)apr_array_push(st->global_certs);
+    /* add the certificate to the client array */
+    cert = (apr_ldap_opt_tls_cert_t *)apr_array_push(dc->client_certs);
     cert->type = cert_type;
     cert->path = file;
     cert->password = password;
 
     /* if file is a file or path, fix the path */
     if (cert_type != APR_LDAP_CA_TYPE_UNKNOWN &&
