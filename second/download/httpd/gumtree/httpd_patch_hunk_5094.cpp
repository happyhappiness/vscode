 **
 **  OpenSSL Callback Functions
 **  _________________________________________________________________
 */
 
 /*
- * Handle out temporary RSA private keys on demand
- *
- * The background of this as the TLSv1 standard explains it:
- *
- * | D.1. Temporary RSA keys
- * |
- * |    US Export restrictions limit RSA keys used for encryption to 512
- * |    bits, but do not place any limit on lengths of RSA keys used for
- * |    signing operations. Certificates often need to be larger than 512
- * |    bits, since 512-bit RSA keys are not secure enough for high-value
- * |    transactions or for applications requiring long-term security. Some
- * |    certificates are also designated signing-only, in which case they
- * |    cannot be used for key exchange.
- * |
- * |    When the public key in the certificate cannot be used for encryption,
- * |    the server signs a temporary RSA key, which is then exchanged. In
- * |    exportable applications, the temporary RSA key should be the maximum
- * |    allowable length (i.e., 512 bits). Because 512-bit RSA keys are
- * |    relatively insecure, they should be changed often. For typical
- * |    electronic commerce applications, it is suggested that keys be
- * |    changed daily or every 500 transactions, and more often if possible.
- * |    Note that while it is acceptable to use the same temporary key for
- * |    multiple transactions, it must be signed each time it is used.
- * |
- * |    RSA key generation is a time-consuming process. In many cases, a
- * |    low-priority process can be assigned the task of key generation.
- * |    Whenever a new key is completed, the existing temporary key can be
- * |    replaced with the new one.
- *
- * XXX: base on comment above, if thread support is enabled,
- * we should spawn a low-priority thread to generate new keys
- * on the fly.
- *
- * So we generated 512 and 1024 bit temporary keys on startup
- * which we now just hand out on demand....
+ * Grab well-defined DH parameters from OpenSSL, see <openssl/bn.h>
+ * (get_rfc*) for all available primes.
  */
-
-RSA *ssl_callback_TmpRSA(SSL *ssl, int export, int keylen)
-{
-    conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
-    SSLModConfigRec *mc = myModConfigFromConn(c);
-    int idx;
-
-    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c,
-                  "handing out temporary %d bit RSA key", keylen);
-
-    /* doesn't matter if export flag is on,
-     * we won't be asked for keylen > 512 in that case.
-     * if we are asked for a keylen > 1024, it is too expensive
-     * to generate on the fly.
-     * XXX: any reason not to generate 2048 bit keys at startup?
-     */
-
-    switch (keylen) {
-      case 512:
-        idx = SSL_TMP_KEY_RSA_512;
-        break;
-
-      case 1024:
-      default:
-        idx = SSL_TMP_KEY_RSA_1024;
-    }
-
-    return (RSA *)mc->pTmpKeys[idx];
+#define make_get_dh(rfc,size,gen) \
+static DH *get_dh##size(void) \
+{ \
+    DH *dh; \
+    if (!(dh = DH_new())) { \
+        return NULL; \
+    } \
+    dh->p = get_##rfc##_prime_##size(NULL); \
+    BN_dec2bn(&dh->g, #gen); \
+    if (!dh->p || !dh->g) { \
+        DH_free(dh); \
+        return NULL; \
+    } \
+    return dh; \
 }
 
 /*
- * Hand out the already generated DH parameters...
+ * Prepare DH parameters from 1024 to 4096 bits, in 1024-bit increments
+ */
+make_get_dh(rfc2409, 1024, 2)
+make_get_dh(rfc3526, 2048, 2)
+make_get_dh(rfc3526, 3072, 2)
+make_get_dh(rfc3526, 4096, 2)
+
+/*
+ * Hand out standard DH parameters, based on the authentication strength
  */
 DH *ssl_callback_TmpDH(SSL *ssl, int export, int keylen)
 {
     conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
-    SSLModConfigRec *mc = myModConfigFromConn(c);
-    int idx;
-
-    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c,
-                  "handing out temporary %d bit DH key", keylen);
+    EVP_PKEY *pkey = SSL_get_privatekey(ssl);
+    int type = pkey ? EVP_PKEY_type(pkey->type) : EVP_PKEY_NONE;
 
-    switch (keylen) {
-      case 512:
-        idx = SSL_TMP_KEY_DH_512;
-        break;
-
-      case 1024:
-      default:
-        idx = SSL_TMP_KEY_DH_1024;
+    /*
+     * OpenSSL will call us with either keylen == 512 or keylen == 1024
+     * (see the definition of SSL_EXPORT_PKEYLENGTH in ssl_locl.h).
+     * Adjust the DH parameter length according to the size of the
+     * RSA/DSA private key used for the current connection, and always
+     * use at least 1024-bit parameters.
+     * Note: This may cause interoperability issues with implementations
+     * which limit their DH support to 1024 bit - e.g. Java 7 and earlier.
+     * In this case, SSLCertificateFile can be used to specify fixed
+     * 1024-bit DH parameters (with the effect that OpenSSL skips this
+     * callback).
+     */
+    if ((type == EVP_PKEY_RSA) || (type == EVP_PKEY_DSA)) {
+        keylen = EVP_PKEY_bits(pkey);
     }
 
-    return (DH *)mc->pTmpKeys[idx];
-}
-
-#ifndef OPENSSL_NO_EC
-EC_KEY *ssl_callback_TmpECDH(SSL *ssl, int export, int keylen)
-{
-    conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
-    SSLModConfigRec *mc = myModConfigFromConn(c);
-    int idx;
-
-    /* XXX Uses 256-bit key for now. TODO: support other sizes. */
     ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c,
-                  "handing out temporary 256 bit ECC key");
+                  "handing out built-in DH parameters for %d-bit authenticated connection", keylen);
 
-    switch (keylen) {
-      case 256:
-      default:
-        idx = SSL_TMP_KEY_EC_256;
-    }
-
-    return (EC_KEY *)mc->pTmpKeys[idx];
+    if (keylen >= 4096)
+        return get_dh4096();
+    else if (keylen >= 3072)
+        return get_dh3072();
+    else if (keylen >= 2048)
+        return get_dh2048();
+    else
+        return get_dh1024();
 }
-#endif
 
 /*
  * This OpenSSL callback function is called when OpenSSL
  * does client authentication and verifies the certificate chain.
  */
 int ssl_callback_SSLVerify(int ok, X509_STORE_CTX *ctx)
