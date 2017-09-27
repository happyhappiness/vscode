     }
 
     if ((ncerts = sk_X509_INFO_num(sk)) <= 0) {
         sk_X509_INFO_free(sk);
         ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s, APLOGNO(02206)
                      "no client certs found for SSL proxy");
-        return;
+        return APR_SUCCESS;
     }
 
     /* Check that all client certs have got certificates and private
      * keys. */
     for (n = 0; n < ncerts; n++) {
         X509_INFO *inf = sk_X509_INFO_value(sk, n);
