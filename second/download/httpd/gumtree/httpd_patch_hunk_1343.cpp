     }
 
     ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                  "loaded %d client certs for SSL proxy",
                  ncerts);
     pkp->certs = sk;
+
+    if (!pkp->ca_cert_file || !store) {
+        return;
+    }
+
+    /* Load all of the CA certs and construct a chain */
+    pkp->ca_certs = (STACK_OF(X509) **) apr_pcalloc(p, ncerts * sizeof(sk));
+    sctx = X509_STORE_CTX_new();
+
+    if (!sctx) {
+        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s,
+                     "SSL proxy client cert initialization failed");
+        ssl_log_ssl_error(APLOG_MARK, APLOG_EMERG, s);
+        ssl_die();
+    }
+
+    X509_STORE_load_locations(store, pkp->ca_cert_file, NULL);
+
+    for (n = 0; n < ncerts; n++) {
+        int i;
+
+        X509_INFO *inf = sk_X509_INFO_value(pkp->certs, n);
+        X509_NAME *name = X509_get_subject_name(inf->x509);
+        char *cert_dn = SSL_X509_NAME_to_string(ptemp, name, 0);
+        X509_STORE_CTX_init(sctx, store, inf->x509, NULL);
+
+        /* Attempt to verify the client cert */
+        if (X509_verify_cert(sctx) != 1) {
+            int err = X509_STORE_CTX_get_error(sctx);
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+                         "SSL proxy client cert chain verification failed for %s: %s",
+                         cert_dn, X509_verify_cert_error_string(err));
+        }
+
+        /* Clear X509_verify_cert errors */
+        ERR_clear_error();
+
+        /* Obtain a copy of the verified chain */
+        chain = X509_STORE_CTX_get1_chain(sctx);
+
+        if (chain != NULL) {
+            /* Discard end entity cert from the chain */
+            X509_free(sk_X509_shift(chain));
+
+            if ((i = sk_X509_num(chain)) > 0) {
+                /* Store the chain for later use */
+                pkp->ca_certs[n] = chain;
+            }
+            else {
+                /* Discard empty chain */
+                sk_X509_pop_free(chain, X509_free);
+                pkp->ca_certs[n] = NULL;
+            }
+
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
+                         "loaded %i intermediate CA%s for cert %i (%s)",
+                         i, i == 1 ? "" : "s", n, cert_dn);
+            if (i > 0) {
+                int j;
+                for (j = 0; j < i; j++) {
+                    X509_NAME *ca_name = X509_get_subject_name(sk_X509_value(chain, j));
+                    char *ca_dn = SSL_X509_NAME_to_string(ptemp, ca_name, 0);
+                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, "%i: %s", j, ca_dn);
+                }
+            }
+        }
+
+        /* get ready for next X509_STORE_CTX_init */
+        X509_STORE_CTX_cleanup(sctx);
+    }
+
+    X509_STORE_CTX_free(sctx);
 }
 
 static void ssl_init_proxy_ctx(server_rec *s,
                                apr_pool_t *p,
                                apr_pool_t *ptemp,
                                SSLSrvConfigRec *sc)
