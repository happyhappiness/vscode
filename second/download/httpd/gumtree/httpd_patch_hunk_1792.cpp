             at = ssl_util_algotypeof(NULL, pPrivateKey);
             an = ssl_util_algotypestr(at);
             if (algoKey & at) {
                 ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                              "Init: Multiple %s server private keys not "
                              "allowed", an);
-                ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, s);
+                ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
                 ssl_die();
             }
             algoKey |= at;
 
             /*
              * Log the type of reading
