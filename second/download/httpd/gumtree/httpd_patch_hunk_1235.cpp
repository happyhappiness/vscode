 
 static int ssl_tmp_key_init_rsa(server_rec *s,
                                 int bits, int idx)
 {
     SSLModConfigRec *mc = myModConfig(s);
 
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
     if (!(mc->pTmpKeys[idx] =
           RSA_generate_key(bits, RSA_F4, NULL, NULL)))
     {
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                      "Init: Failed to generate temporary "
                      "%d bit RSA private key", bits);
+        ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, s);
         return !OK;
     }
 
     return OK;
 }
 
 static int ssl_tmp_key_init_dh(server_rec *s,
                                int bits, int idx)
 {
     SSLModConfigRec *mc = myModConfig(s);
 
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
     if (!(mc->pTmpKeys[idx] =
           ssl_dh_GetTmpParam(bits)))
     {
         ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                      "Init: Failed to generate temporary "
                      "%d bit DH parameters", bits);
