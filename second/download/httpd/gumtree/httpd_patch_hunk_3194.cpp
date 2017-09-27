 
     /*
      * Walk through all configured servers
      */
     for (pServ = s; pServ != NULL; pServ = pServ->next) {
         sc = mySrvConfig(pServ);
-
-        if (!sc->enabled)
+        cpVHostID = ssl_util_vhostid(p, pServ);
+        if (!sc->enabled) {
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, pServ, APLOGNO(02199)
+                         "SSL not enabled on vhost %s, skipping SSL setup",
+                         cpVHostID);
             continue;
+        }
 
-        cpVHostID = ssl_util_vhostid(p, pServ);
-        ap_log_error(APLOG_MARK, APLOG_INFO, 0, pServ,
-                     "Loading certificate & private key of SSL-aware server");
+        ap_log_error(APLOG_MARK, APLOG_INFO, 0, pServ, APLOGNO(02200)
+                     "Loading certificate & private key of SSL-aware server '%s'",
+                     cpVHostID);
 
         /*
          * Read in server certificate(s): This is the easy part
          * because this file isn't encrypted in any way.
          */
         if (sc->server->pks->cert_files[0] == NULL
             && sc->server->pkcs7 == NULL) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, 0, pServ,
+            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, pServ, APLOGNO(02240)
                          "Server should be SSL-aware but has no certificate "
                          "configured [Hint: SSLCertificateFile] (%s:%d)",
                          pServ->defn_name, pServ->defn_line_number);
             ssl_die();
         }
 
+        /* Bitmasks for all key algorithms configured for this server;
+         * initialize to zero. */
         algoCert = SSL_ALGO_UNKNOWN;
         algoKey  = SSL_ALGO_UNKNOWN;
+
+        /* Iterate through configured certificate files for this
+         * server. */
         for (i = 0, j = 0; i < SSL_AIDX_MAX
                  && (sc->server->pks->cert_files[i] != NULL
                      || sc->server->pkcs7); i++) {
+            const char *key_id;
+            int using_cache = 0;
+
             if (sc->server->pkcs7) {
                 STACK_OF(X509) *certs = ssl_read_pkcs7(pServ,
                                                        sc->server->pkcs7);
                 pX509Cert = sk_X509_value(certs, 0);
                 i = SSL_AIDX_MAX;
             } else {
                 apr_cpystrn(szPath, sc->server->pks->cert_files[i],
                             sizeof(szPath));
                 if ((rv = exists_and_readable(szPath, p, NULL))
                     != APR_SUCCESS) {
-                    ap_log_error(APLOG_MARK, APLOG_ERR, rv, s,
+                    ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(02201)
                                  "Init: Can't open server certificate file %s",
                                  szPath);
                     ssl_die();
                 }
                 if ((pX509Cert = SSL_read_X509(szPath, NULL, NULL)) == NULL) {
-                    ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
+                    ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02241)
                                  "Init: Unable to read server certificate from"
                                  " file %s", szPath);
-                    ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
+                    ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
                     ssl_die();
                 }
+                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02202)
+                             "Init: Read server certificate from '%s'",
+                             szPath);
             }
             /*
              * check algorithm type of certificate and make
              * sure only one certificate per type is used.
              */
             at = ssl_util_algotypeof(pX509Cert, NULL);
             an = ssl_util_algotypestr(at);
             if (algoCert & at) {
-                ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
+                ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02242)
                              "Init: Multiple %s server certificates not "
                              "allowed", an);
-                ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
+                ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
                 ssl_die();
             }
             algoCert |= at;
 
+            /* Determine the hash key used for this (vhost, algo-type)
+             * pair used to index both the mc->tPrivateKey and
+             * mc->tPublicCert tables: */
+            key_id = asn1_table_vhost_key(mc, p, cpVHostID, an);
+
             /*
              * Insert the certificate into global module configuration to let it
              * survive the processing between the 1st Apache API init round (where
              * we operate here) and the 2nd Apache init round (where the
              * certificate is actually used to configure mod_ssl's per-server
              * configuration structures).
              */
-            cp = asn1_table_vhost_key(mc, p, cpVHostID, an);
             length = i2d_X509(pX509Cert, NULL);
-            ucp = ssl_asn1_table_set(mc->tPublicCert, cp, length);
+            ucp = ssl_asn1_table_set(mc->tPublicCert, key_id, length);
             (void)i2d_X509(pX509Cert, &ucp); /* 2nd arg increments */
 
             /*
              * Free the X509 structure
              */
             X509_free(pX509Cert);
