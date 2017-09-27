     if (mc->szCryptoDevice) {
         if (!(e = ENGINE_by_id(mc->szCryptoDevice))) {
             ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01888)
                          "Init: Failed to load Crypto Device API `%s'",
                          mc->szCryptoDevice);
             ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
-            ssl_die();
+            ssl_die(s);
         }
 
         if (strEQ(mc->szCryptoDevice, "chil")) {
             ENGINE_ctrl(e, ENGINE_CTRL_CHIL_SET_FORKCHECK, 1, 0, 0);
         }
 
         if (!ENGINE_set_default(e, ENGINE_METHOD_ALL)) {
             ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01889)
                          "Init: Failed to enable Crypto Device API `%s'",
                          mc->szCryptoDevice);
             ssl_log_ssl_error(SSLLOG_MARK, APLOG_EMERG, s);
-            ssl_die();
+            ssl_die(s);
         }
         ap_log_error(APLOG_MARK, APLOG_INFO, 0, s, APLOGNO(01890)
                      "Init: loaded Crypto Device API `%s'",
                      mc->szCryptoDevice);
 
         ENGINE_free(e);
