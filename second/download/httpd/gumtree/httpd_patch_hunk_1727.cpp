 
     ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                  "%s compiled against Server: %s, Library: %s",
                  modver, AP_SERVER_BASEVERSION, incver);
 }
 
+
+/*
+ * Handle the Temporary RSA Keys and DH Params
+ */
+
+#define MODSSL_TMP_KEY_FREE(mc, type, idx) \
+    if (mc->pTmpKeys[idx]) { \
+        type##_free((type *)mc->pTmpKeys[idx]); \
+        mc->pTmpKeys[idx] = NULL; \
+    }
+
+#define MODSSL_TMP_KEYS_FREE(mc, type) \
+    MODSSL_TMP_KEY_FREE(mc, type, SSL_TMP_KEY_##type##_512); \
+    MODSSL_TMP_KEY_FREE(mc, type, SSL_TMP_KEY_##type##_1024)
+
+static void ssl_tmp_keys_free(server_rec *s)
+{
+    SSLModConfigRec *mc = myModConfig(s);
+
+    MODSSL_TMP_KEYS_FREE(mc, RSA);
+    MODSSL_TMP_KEYS_FREE(mc, DH);
+}
+
+static int ssl_tmp_key_init_rsa(server_rec *s,
+                                int bits, int idx)
+{
+    SSLModConfigRec *mc = myModConfig(s);
+
+#ifdef HAVE_FIPS
+
+    if (FIPS_mode() && bits < 1024) {
+        mc->pTmpKeys[idx] = NULL;
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
+                     "Init: Skipping generating temporary "
+                     "%d bit RSA private key in FIPS mode", bits);
+        return OK;
+    }
+
+#endif
+
+    if (!(mc->pTmpKeys[idx] =
+          RSA_generate_key(bits, RSA_F4, NULL, NULL)))
+    {
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
+                     "Init: Failed to generate temporary "
+                     "%d bit RSA private key", bits);
+        ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
+        return !OK;
+    }
+
+    return OK;
+}
+
+static int ssl_tmp_key_init_dh(server_rec *s,
+                               int bits, int idx)
+{
+    SSLModConfigRec *mc = myModConfig(s);
+
+#ifdef HAVE_FIPS
+
+    if (FIPS_mode() && bits < 1024) {
+        mc->pTmpKeys[idx] = NULL;
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
+                     "Init: Skipping generating temporary "
+                     "%d bit DH parameters in FIPS mode", bits);
+        return OK;
+    }
+
+#endif
+
+    if (!(mc->pTmpKeys[idx] =
+          ssl_dh_GetTmpParam(bits)))
+    {
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
+                     "Init: Failed to generate temporary "
+                     "%d bit DH parameters", bits);
+        return !OK;
+    }
+
+    return OK;
+}
+
+#define MODSSL_TMP_KEY_INIT_RSA(s, bits) \
+    ssl_tmp_key_init_rsa(s, bits, SSL_TMP_KEY_RSA_##bits)
+
+#define MODSSL_TMP_KEY_INIT_DH(s, bits) \
+    ssl_tmp_key_init_dh(s, bits, SSL_TMP_KEY_DH_##bits)
+
+static int ssl_tmp_keys_init(server_rec *s)
+{
+    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, s,
+                 "Init: Generating temporary RSA private keys (512/1024 bits)");
+
+    if (MODSSL_TMP_KEY_INIT_RSA(s, 512) ||
+        MODSSL_TMP_KEY_INIT_RSA(s, 1024)) {
+        return !OK;
+    }
+
+    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, s,
+                 "Init: Generating temporary DH parameters (512/1024 bits)");
+
+    if (MODSSL_TMP_KEY_INIT_DH(s, 512) ||
+        MODSSL_TMP_KEY_INIT_DH(s, 1024)) {
+        return !OK;
+    }
+
+    return OK;
+}
+
 /*
  *  Per-module initialization
  */
 int ssl_init_Module(apr_pool_t *p, apr_pool_t *plog,
                     apr_pool_t *ptemp,
                     server_rec *base_server)
