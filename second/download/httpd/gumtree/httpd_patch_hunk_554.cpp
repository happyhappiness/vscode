 {
     ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                  "Init: Initializing %s library", SSL_LIBRARY_NAME);
 
     SSL_load_error_strings();
     SSL_library_init();
+    OpenSSL_add_all_algorithms(); /* Required for eg SHA256 client certs */
 }
 
 /*
  * Handle the Temporary RSA Keys and DH Params
  */
 
