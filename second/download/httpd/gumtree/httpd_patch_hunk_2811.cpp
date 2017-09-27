         }
     }
     else {
         return "Certificate type was not specified.";
     }
 
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server,
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, cmd->server, APLOGNO(01305)
                       "LDAP: SSL trusted client cert - %s (type %s)",
                        file, type);
 
     /* add the certificate to the client array */
     cert = (apr_ldap_opt_tls_cert_t *)apr_array_push(dc->client_certs);
     cert->type = cert_type;
