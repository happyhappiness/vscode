             at = ssl_util_algotypeof(pX509Cert, NULL);
             an = ssl_util_algotypestr(at);
             if (algoCert & at) {
                 ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                              "Init: Multiple %s server certificates not "
                              "allowed", an);
-                ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, s);
+                ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
                 ssl_die();
             }
             algoCert |= at;
 
             /*
              * Insert the certificate into global module configuration to let it
