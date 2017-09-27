 
     for (n = 0; n < sk_X509_NAME_num(sk); n++) {
         X509_NAME *name = sk_X509_NAME_value(sk, n);
 
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02209)
                      "CA certificate: %s",
-                     SSL_X509_NAME_to_string(ptemp, name, 0));
+                     modssl_X509_NAME_to_string(ptemp, name, 0));
 
         /*
          * note that SSL_load_client_CA_file() checks for duplicates,
          * but since we call it multiple times when reading a directory
          * we must also check for duplicates ourselves.
          */
