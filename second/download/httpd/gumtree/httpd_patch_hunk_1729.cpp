 
     if (mc->szCryptoDevice) {
         if (!(e = ENGINE_by_id(mc->szCryptoDevice))) {
             ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                          "Init: Failed to load Crypto Device API `%s'",
                          mc->szCryptoDevice);
-            ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, s);
+            ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
             ssl_die();
         }
 
         if (strEQ(mc->szCryptoDevice, "chil")) {
             ENGINE_ctrl(e, ENGINE_CTRL_CHIL_SET_FORKCHECK, 1, 0, 0);
         }
 
         if (!ENGINE_set_default(e, ENGINE_METHOD_ALL)) {
             ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                          "Init: Failed to enable Crypto Device API `%s'",
                          mc->szCryptoDevice);
-            ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, s);
+            ssl_log_ssl_error(SSLLOG_MARK, APLOG_ERR, s);
             ssl_die();
         }
         ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, 
                      "Init: loaded Crypto Device API `%s'", 
                      mc->szCryptoDevice);
 
