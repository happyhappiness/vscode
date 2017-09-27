         ap_log_error(APLOG_MARK, APLOG_WARNING, 0, base_server,
                      "Init: You should not use name-based "
                      "virtual hosts in conjunction with SSL!!");
     }
 }
 
+#ifdef SSLC_VERSION_NUMBER
+static int ssl_init_FindCAList_X509NameCmp(char **a, char **b)
+{
+    return(X509_NAME_cmp((void*)*a, (void*)*b));
+}
+#else
 static int ssl_init_FindCAList_X509NameCmp(X509_NAME **a, X509_NAME **b)
 {
     return(X509_NAME_cmp(*a, *b));
 }
+#endif
 
 static void ssl_init_PushCAList(STACK_OF(X509_NAME) *ca_list,
                                 server_rec *s, const char *file)
 {
     int n;
     STACK_OF(X509_NAME) *sk;
 
-    sk = (STACK_OF(X509_NAME) *)SSL_load_client_CA_file(file);
+    sk = (STACK_OF(X509_NAME) *)
+             SSL_load_client_CA_file(MODSSL_PCHAR_CAST file);
 
     if (!sk) {
         return;
     }
 
     for (n = 0; n < sk_X509_NAME_num(sk); n++) {
