                     {
                         ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                                      pServ,
                                      "Init: Unable to read pass phrase "
                                      "[Hint: key introduced or changed "
                                      "before restart?]");
-                        ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, pServ);
+                        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, pServ);
                     }
                     else {
                         ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                                      pServ, "Init: Private key not found");
-                        ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, pServ);
+                        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, pServ);
                     }
                     if (writetty) {
                         apr_file_printf(writetty, "Apache:mod_ssl:Error: Private key not found.\n");
                         apr_file_printf(writetty, "**Stopped\n");
                     }
                 }
                 else {
                     ap_log_error(APLOG_MARK, APLOG_ERR, 0,
                                  pServ, "Init: Pass phrase incorrect");
-                    ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, pServ);
+                    ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, pServ);
 
                     if (writetty) {
                         apr_file_printf(writetty, "Apache:mod_ssl:Error: Pass phrase incorrect.\n");
                         apr_file_printf(writetty, "**Stopped\n");
                     }
                 }
