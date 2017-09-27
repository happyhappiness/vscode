                        APR_OS_DEFAULT, ptemp);
 
     if (rv != APR_SUCCESS) {
         ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02286)
                      "Failed to open ticket key file %s: (%d) %pm",
                      path, rv, &rv);
-        ssl_die();
+        ssl_die(s);
     }
 
     rv = apr_file_read_full(fp, &buf[0], TLSEXT_TICKET_KEY_LEN, &len);
 
     if (rv != APR_SUCCESS) {
         ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02287)
                      "Failed to read %d bytes from %s: (%d) %pm",
                      TLSEXT_TICKET_KEY_LEN, path, rv, &rv);
-        ssl_die();
+        ssl_die(s);
     }
 
     memcpy(ticket_key->key_name, buf, 16);
     memcpy(ticket_key->hmac_secret, buf + 16, 16);
     memcpy(ticket_key->aes_key, buf + 32, 16);
 
     if (!SSL_CTX_set_tlsext_ticket_key_cb(mctx->ssl_ctx,
                                           ssl_callback_SessionTicket)) {
         ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01913)
                      "Unable to initialize TLS session ticket key callback "
                      "(incompatible OpenSSL version?)");
         ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
-        ssl_die();
+        ssl_die(s);
     }
 
     ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(02288)
                  "TLS session ticket key for %s successfully loaded from %s",
                  (mySrvConfig(s))->vhost_id, path);
 }
