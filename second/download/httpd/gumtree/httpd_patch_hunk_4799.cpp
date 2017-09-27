             an = ssl_util_algotypestr(at);
             if (algoKey & at) {
                 ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02248)
                              "Init: Multiple %s server private keys not "
                              "allowed", an);
                 ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
-                ssl_die();
+                ssl_die(s);
             }
             algoKey |= at;
 
             /*
              * Log the type of reading
              */
