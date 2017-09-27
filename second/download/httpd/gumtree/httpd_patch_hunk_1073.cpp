 #endif
     SSL_load_error_strings();
     SSL_library_init();
     bio_out=BIO_new_fp(stdout,BIO_NOCLOSE);
     bio_err=BIO_new_fp(stderr,BIO_NOCLOSE);
 
-    /* TODO: Allow force SSLv2_client_method() (TLSv1?) */
-    if (!(ctx = SSL_CTX_new(SSLv23_client_method()))) {
-	fprintf(stderr, "Could not init SSL CTX");
+    if (!(ssl_ctx = SSL_CTX_new(meth))) {
+        BIO_printf(bio_err, "Could not initialize SSL Context.\n");
+        ERR_print_errors(bio_err);
+        exit(1);
+    }
+    SSL_CTX_set_options(ssl_ctx, SSL_OP_ALL);
+    if (ssl_cipher != NULL) {
+        if (!SSL_CTX_set_cipher_list(ssl_ctx, ssl_cipher)) {
+            fprintf(stderr, "error setting cipher list [%s]\n", ssl_cipher);
 	ERR_print_errors_fp(stderr);
 	exit(1);
     }
-    SSL_CTX_set_options(ctx, SSL_OP_ALL);
-#ifdef USE_THREADS
-    ssl_util_thread_setup(cntxt);
-#endif
+    }
+    if (verbosity >= 3) {
+        SSL_CTX_set_info_callback(ssl_ctx, ssl_state_cb);
+    }
 #endif
 #ifdef SIGPIPE
     apr_signal(SIGPIPE, SIG_IGN);       /* Ignore writes to connections that
 					 * have been closed at the other end. */
 #endif
     copyright();
