             if (pPrivateKey == NULL) {
                 ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02247)
                             "Init: Unable to read server private key from "
                             "file %s [Hint: Perhaps it is in a separate file? "
                             "  See SSLCertificateKeyFile]", szPath);
                 ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
-                ssl_die();
+                ssl_die(s);
             }
 
             /*
              * check algorithm type of private key and make
              * sure only one private key per type is used.
              */
