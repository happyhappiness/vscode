     }
 
     if (pkp->cert_path) {
         SSL_X509_INFO_load_path(ptemp, sk, pkp->cert_path);
     }
 
-    if ((ncerts = sk_X509_INFO_num(sk)) > 0) {
-        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
-                     "loaded %d client certs for SSL proxy",
-                     ncerts);
-
-        pkp->certs = sk;
-    }
-    else {
+    if ((ncerts = sk_X509_INFO_num(sk)) <= 0) {
+        sk_X509_INFO_free(sk);
         ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                      "no client certs found for SSL proxy");
-        sk_X509_INFO_free(sk);
+        return;
+    }
+
+    /* Check that all client certs have got certificates and private
+     * keys. */
+    for (n = 0; n < ncerts; n++) {
+        X509_INFO *inf = sk_X509_INFO_value(sk, n);
+
+        if (!inf->x509 || !inf->x_pkey) {
+            sk_X509_INFO_free(sk);
+            ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, s,
+                         "incomplete client cert configured for SSL proxy "
+                         "(missing or encrypted private key?)");
+            ssl_die();
+            return;
+        }
     }
+
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+                 "loaded %d client certs for SSL proxy",
+                 ncerts);
+    pkp->certs = sk;
 }
 
 static void ssl_init_proxy_ctx(server_rec *s,
                                apr_pool_t *p,
                                apr_pool_t *ptemp,
                                SSLSrvConfigRec *sc)
