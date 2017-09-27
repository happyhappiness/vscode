         ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01914)
                      "Configuring server %s for SSL protocol", sc->vhost_id);
         if ((rv = ssl_init_server_ctx(s, p, ptemp, sc, pphrases))
             != APR_SUCCESS) {
             return rv;
         }
+
+	/* Initialize OCSP Responder certificate if OCSP enabled */
+	#ifndef OPENSSL_NO_OCSP
+        	ssl_init_ocsp_certificates(s, sc->server);
+	#endif
+
     }
 
     if (sc->proxy_enabled) {
         if ((rv = ssl_init_proxy_ctx(s, p, ptemp, sc)) != APR_SUCCESS) {
             return rv;
         }
