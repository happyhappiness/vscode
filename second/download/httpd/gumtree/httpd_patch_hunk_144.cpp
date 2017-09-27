     ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, result, s, 
                       "[%d] ldap cache init: %s", 
                       getpid(), buf);
 }
 
 
+static apr_status_t util_ldap_cleanup_module(void *data)
+{
+    server_rec *s = data;
+
+    util_ldap_state_t *st = (util_ldap_state_t *)ap_get_module_config(
+                                          s->module_config, &ldap_module);
+
+    #if APR_HAS_LDAP_SSL
+        #if APR_HAS_NOVELL_LDAPSDK
+            if (st->ssl_support)
+                ldapssl_client_deinit();
+        #endif
+    #endif
+   
+    return(APR_SUCCESS);
+}
+
+static int util_ldap_post_config(apr_pool_t *p, apr_pool_t *plog, 
+                                 apr_pool_t *ptemp, server_rec *s)
+{
+    int rc = LDAP_SUCCESS;
+
+    util_ldap_state_t *st = (util_ldap_state_t *)ap_get_module_config(
+                                                s->module_config, 
+                                                &ldap_module);
+
+        /* log the LDAP SDK used 
+        */
+    #if APR_HAS_NETSCAPE_LDAPSDK 
+    
+        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, 
+             "LDAP: Built with Netscape LDAP SDK" );
+
+    #elif APR_HAS_NOVELL_LDAPSDK
+
+        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, 
+             "LDAP: Built with Novell LDAP SDK" );
+
+    #elif APR_HAS_OPENLDAP_LDAPSDK
+
+        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, 
+             "LDAP: Built with OpenLDAP LDAP SDK" );
+
+    #elif APR_HAS_MICROSOFT_LDAPSDK
+    
+        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, 
+             "LDAP: Built with Microsoft LDAP SDK" );
+    #else
+    
+        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, 
+             "LDAP: Built with unknown LDAP SDK" );
+
+    #endif /* APR_HAS_NETSCAPE_LDAPSDK */
+
+
+
+    apr_pool_cleanup_register(p, s, util_ldap_cleanup_module,
+                              util_ldap_cleanup_module); 
+
+    /* initialize SSL support if requested
+    */
+    if (st->cert_auth_file)
+    {
+        #if APR_HAS_LDAP_SSL /* compiled with ssl support */
+
+        #if APR_HAS_NETSCAPE_LDAPSDK 
+
+            /* Netscape sdk only supports a cert7.db file 
+            */
+            if (st->cert_file_type == LDAP_CA_TYPE_CERT7_DB)
+            {
+                rc = ldapssl_client_init(st->cert_auth_file, NULL);
+            }
+            else
+            {
+                ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s, 
+                         "LDAP: Invalid LDAPTrustedCAType directive - "
+                          "CERT7_DB_PATH type required");
+                rc = -1;
+            }
+
+        #elif APR_HAS_NOVELL_LDAPSDK
+        
+            /* Novell SDK supports DER or BASE64 files
+            */
+            if (st->cert_file_type == LDAP_CA_TYPE_DER  ||
+                st->cert_file_type == LDAP_CA_TYPE_BASE64 )
+            {
+                rc = ldapssl_client_init(NULL, NULL);
+                if (LDAP_SUCCESS == rc)
+                {
+                    if (st->cert_file_type == LDAP_CA_TYPE_BASE64)
+                        rc = ldapssl_add_trusted_cert(st->cert_auth_file, 
+                                                  LDAPSSL_CERT_FILETYPE_B64);
+                    else
+                        rc = ldapssl_add_trusted_cert(st->cert_auth_file, 
+                                                  LDAPSSL_CERT_FILETYPE_DER);
+
+                    if (LDAP_SUCCESS != rc)
+                        ldapssl_client_deinit();
+                }
+            }
+            else
+            {
+                ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s, 
+                             "LDAP: Invalid LDAPTrustedCAType directive - "
+                             "DER_FILE or BASE64_FILE type required");
+                rc = -1;
+            }
+
+        #elif APR_HAS_OPENLDAP_LDAPSDK
+
+            /* OpenLDAP SDK supports BASE64 files
+            */
+            if (st->cert_file_type == LDAP_CA_TYPE_BASE64)
+            {
+                rc = ldap_set_option(NULL, LDAP_OPT_X_TLS_CACERTFILE, st->cert_auth_file);
+            }
+            else
+            {
+                ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s, 
+                             "LDAP: Invalid LDAPTrustedCAType directive - "
+                             "BASE64_FILE type required");
+                rc = -1;
+            }
+
+
+        #elif APR_HAS_MICROSOFT_LDAPSDK
+            
+            /* Microsoft SDK use the registry certificate store - always
+             * assume support is always available
+            */
+            rc = LDAP_SUCCESS;
+
+        #else
+            rc = -1;
+        #endif /* APR_HAS_NETSCAPE_LDAPSDK */
+
+        #else  /* not compiled with SSL Support */
+
+            ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, 
+                     "LDAP: Not built with SSL support." );
+            rc = -1;
+
+        #endif /* APR_HAS_LDAP_SSL */
+
+        if (LDAP_SUCCESS == rc)
+        {
+            st->ssl_support = 1;
+        }
+        else
+        {
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, 
+                         "LDAP: SSL initialization failed");
+            st->ssl_support = 0;
+        }
+    }
+      
+        /* The Microsoft SDK uses the registry certificate store -
+         * always assume support is available
+        */
+    #if APR_HAS_MICROSOFT_LDAPSDK
+        st->ssl_support = 1;
+    #endif
+    
+
+        /* log SSL status - If SSL isn't available it isn't necessarily
+         * an error because the modules asking for LDAP connections 
+         * may not ask for SSL support
+        */
+    if (st->ssl_support)
+    {
+       ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, 
+                         "LDAP: SSL support available" );
+    }
+    else
+    {
+       ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, 
+                         "LDAP: SSL support unavailable" );
+    }
+    
+    return(OK);
+}
+
+
 command_rec util_ldap_cmds[] = {
     AP_INIT_TAKE1("LDAPSharedCacheSize", util_ldap_set_cache_bytes, NULL, RSRC_CONF,
                   "Sets the size of the shared memory cache in bytes. "
                   "Zero means disable the shared memory cache. Defaults to 100KB."),
 
     AP_INIT_TAKE1("LDAPCacheEntries", util_ldap_set_cache_entries, NULL, RSRC_CONF,
