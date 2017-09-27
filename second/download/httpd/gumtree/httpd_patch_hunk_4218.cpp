 }
 
 #ifndef OPENSSL_NO_EC
 EC_KEY *ssl_callback_TmpECDH(SSL *ssl, int export, int keylen)
 {
     conn_rec *c = (conn_rec *)SSL_get_app_data(ssl);
-    static EC_KEY *ecdh = NULL;
-    static int init = 0;
+    SSLModConfigRec *mc = myModConfigFromConn(c);
+    int idx;
 
     /* XXX Uses 256-bit key for now. TODO: support other sizes. */
     ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c,
                   "handing out temporary 256 bit ECC key");
 
-    if (init == 0) {
-        ecdh = EC_KEY_new();
-        if (ecdh != NULL) {
-            /* ecdh->group = EC_GROUP_new_by_nid(NID_secp160r2); */
-            EC_KEY_set_group(ecdh,
-              EC_GROUP_new_by_curve_name(NID_X9_62_prime256v1));
-        }
-        init = 1;
+    switch (keylen) {
+      case 256:
+      default:
+        idx = SSL_TMP_KEY_EC_256;
     }
 
-    return ecdh;
+    return (EC_KEY *)mc->pTmpKeys[idx];
 }
 #endif
 
 /*
  * This OpenSSL callback function is called when OpenSSL
  * does client authentication and verifies the certificate chain.
