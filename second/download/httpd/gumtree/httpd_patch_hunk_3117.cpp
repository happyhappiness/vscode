     SSLModConfigRec *mc = myModConfig(s);
 
 #ifdef HAVE_FIPS
 
     if (FIPS_mode() && bits < 1024) {
         mc->pTmpKeys[idx] = NULL;
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01877)
                      "Init: Skipping generating temporary "
                      "%d bit RSA private key in FIPS mode", bits);
         return OK;
     }
 
 #endif
-
+#ifdef HAVE_GENERATE_EX
+    {
+        RSA *tkey;
+        BIGNUM *bn_f4;
+        if (!(tkey = RSA_new())
+          || !(bn_f4 = BN_new())
+          || !BN_set_word(bn_f4, RSA_F4)
+          || !RSA_generate_key_ex(tkey, bits, bn_f4, NULL))
+        {
+            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01878)
+                         "Init: Failed to generate temporary "
+                         "%d bit RSA private key", bits);
+            ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
+            return !OK;
+        }
+        BN_free(bn_f4);
+        mc->pTmpKeys[idx] = tkey;
+    }
+#else
     if (!(mc->pTmpKeys[idx] =
           RSA_generate_key(bits, RSA_F4, NULL, NULL)))
     {
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(01879)
                      "Init: Failed to generate temporary "
                      "%d bit RSA private key", bits);
         ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
         return !OK;
     }
+#endif
 
     return OK;
 }
 
 static int ssl_tmp_key_init_dh(server_rec *s,
                                int bits, int idx)
