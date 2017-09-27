     }
     free(asn1);
 
     apr_hash_set(table, key, klen, NULL);
 }
 
-#ifdef HAVE_ECC
-static const char *ssl_asn1_key_types[] = {"RSA", "DSA", "ECC"};
-#else
-static const char *ssl_asn1_key_types[] = {"RSA", "DSA"};
-#endif
-
-const char *ssl_asn1_keystr(int keytype)
-{
-    if (keytype >= SSL_AIDX_MAX) {
-        return NULL;
-    }
-
-    return ssl_asn1_key_types[keytype];
-}
-
-const char *ssl_asn1_table_keyfmt(apr_pool_t *p,
-                                  const char *id,
-                                  int keytype)
-{
-    const char *keystr = ssl_asn1_keystr(keytype);
-
-    return apr_pstrcat(p, id, ":", keystr, NULL);
-}
-
-STACK_OF(X509) *ssl_read_pkcs7(server_rec *s, const char *pkcs7)
-{
-    PKCS7 *p7;
-    STACK_OF(X509) *certs = NULL;
-    FILE *f;
-
-    f = fopen(pkcs7, "r");
-    if (!f) {
-        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02212) "Can't open %s", pkcs7);
-        ssl_die(s);
-    }
-
-    p7 = PEM_read_PKCS7(f, NULL, NULL, NULL);
-    if (!p7) {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(02274)
-                     "Can't read PKCS7 object %s", pkcs7);
-        ssl_log_ssl_error(SSLLOG_MARK, APLOG_CRIT, s);
-        exit(1);
-    }
-
-    switch (OBJ_obj2nid(p7->type)) {
-    case NID_pkcs7_signed:
-        certs = p7->d.sign->cert;
-        p7->d.sign->cert = NULL;
-        PKCS7_free(p7);
-        break;
-
-    case NID_pkcs7_signedAndEnveloped:
-        certs = p7->d.signed_and_enveloped->cert;
-        p7->d.signed_and_enveloped->cert = NULL;
-        PKCS7_free(p7);
-        break;
-
-    default:
-        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02213)
-                     "Don't understand PKCS7 file %s", pkcs7);
-        ssl_die(s);
-    }
-
-    if (!certs) {
-        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02214)
-                     "No certificates in %s", pkcs7);
-        ssl_die(s);
-    }
-
-    fclose(f);
-
-    return certs;
-}
-
-
 #if APR_HAS_THREADS
 /*
  * To ensure thread-safetyness in OpenSSL - work in progress
  */
 
 static apr_thread_mutex_t **lock_cs;
