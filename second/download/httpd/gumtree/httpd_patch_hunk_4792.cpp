         if (sc->server->pks->cert_files[0] == NULL
             && sc->server->pkcs7 == NULL) {
             ap_log_error(APLOG_MARK, APLOG_EMERG, 0, pServ, APLOGNO(02240)
                          "Server should be SSL-aware but has no certificate "
                          "configured [Hint: SSLCertificateFile] (%s:%d)",
                          pServ->defn_name, pServ->defn_line_number);
-            ssl_die();
+            ssl_die(pServ);
         }
 
         /* Bitmasks for all key algorithms configured for this server;
          * initialize to zero. */
         algoCert = SSL_ALGO_UNKNOWN;
         algoKey  = SSL_ALGO_UNKNOWN;
