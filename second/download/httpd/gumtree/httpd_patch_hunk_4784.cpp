         || have_ecc
 #endif
 )) {
         ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01910)
                 "Oops, no " KEYTYPES " server certificate found "
                 "for '%s:%d'?!", s->server_hostname, s->port);
-        ssl_die();
+        ssl_die(s);
     }
 
     for (i = 0; i < SSL_AIDX_MAX; i++) {
         ssl_check_public_cert(s, ptemp, mctx->pks->certs[i], i);
     }
 
