                     "Unable to configure verify locations "
                     "for client authentication");
             ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, s);
             ssl_die();
         }
 
-        ca_list = ssl_init_FindCAList(s, ptemp,
-                                      mctx->auth.ca_cert_file,
-                                      mctx->auth.ca_cert_path);
+        if (mctx->pks && (mctx->pks->ca_name_file || mctx->pks->ca_name_path)) {
+            ca_list = ssl_init_FindCAList(s, ptemp,
+                                          mctx->pks->ca_name_file,
+                                          mctx->pks->ca_name_path);
+        } else
+            ca_list = ssl_init_FindCAList(s, ptemp,
+                                          mctx->auth.ca_cert_file,
+                                          mctx->auth.ca_cert_path);
         if (!ca_list) {
             ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
-                    "Unable to determine list of available "
+                    "Unable to determine list of acceptable "
                     "CA certificates for client authentication");
             ssl_die();
         }
 
         SSL_CTX_set_client_CA_list(ctx, (STACK *)ca_list);
     }
