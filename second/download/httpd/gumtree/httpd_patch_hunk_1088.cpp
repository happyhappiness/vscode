     apr_app_initialize(&argc, &argv, NULL);
     atexit(terminate);
     apr_pool_create(&pool, NULL);
     apr_file_open_stderr(&errfile, pool);
 
 #if APR_CHARSET_EBCDIC
-    rv = apr_xlate_open(&to_ascii, "ISO8859-1", APR_DEFAULT_CHARSET, pool);
+    rv = apr_xlate_open(&to_ascii, "ISO-8859-1", APR_DEFAULT_CHARSET, pool);
     if (rv) {
-        apr_file_printf(errfile, "apr_xlate_open(to ASCII)->%d\n", rv);
+        apr_file_printf(errfile, "apr_xlate_open(to ASCII)->%d" NL, rv);
         exit(1);
     }
     rv = apr_SHA1InitEBCDIC(to_ascii);
     if (rv) {
-        apr_file_printf(errfile, "apr_SHA1InitEBCDIC()->%d\n", rv);
+        apr_file_printf(errfile, "apr_SHA1InitEBCDIC()->%d" NL, rv);
         exit(1);
     }
     rv = apr_MD5InitEBCDIC(to_ascii);
     if (rv) {
-        apr_file_printf(errfile, "apr_MD5InitEBCDIC()->%d\n", rv);
+        apr_file_printf(errfile, "apr_MD5InitEBCDIC()->%d" NL, rv);
         exit(1);
     }
 #endif /*APR_CHARSET_EBCDIC*/
 
     check_args(pool, argc, argv, &alg, &mask, &user, &pwfilename, &password);
 
 
 #if defined(WIN32) || defined(NETWARE)
     if (alg == ALG_CRYPT) {
         alg = ALG_APMD5;
-        apr_file_printf(errfile, "Automatically using MD5 format.\n");
+        apr_file_printf(errfile, "Automatically using MD5 format." NL);
     }
 #endif
 
 #if (!(defined(WIN32) || defined(TPF) || defined(NETWARE)))
     if (alg == ALG_PLAIN) {
         apr_file_printf(errfile,"Warning: storing passwords as plain text "
-                        "might just not work on this platform.\n");
+                        "might just not work on this platform." NL);
     }
 #endif
 
     /*
      * Only do the file checks if we're supposed to frob it.
      */
