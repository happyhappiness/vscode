                     long serial = ASN1_INTEGER_get(sn);
 
                     ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                                  "Certificate with serial %ld (0x%lX) "
                                  "revoked per CRL from issuer %s",
                                  serial, serial, cp);
-                    free(cp);
+                    modssl_free(cp);
                 }
 
                 X509_STORE_CTX_set_error(ctx, X509_V_ERR_CERT_REVOKED);
                 X509_OBJECT_free_contents(&obj);
 
                 return FALSE;
