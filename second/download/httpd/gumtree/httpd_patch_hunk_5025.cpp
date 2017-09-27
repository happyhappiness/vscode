     apr_pool_create(&cntxt, NULL);
     apr_file_open_stderr(&errfile, cntxt);
 
 #if APR_CHARSET_EBCDIC
     rv = apr_xlate_open(&to_ascii, "ISO-8859-1", APR_DEFAULT_CHARSET, cntxt);
     if (rv) {
-        apr_file_printf(errfile, "apr_xlate_open(): %s (%d)\n",
-                apr_strerror(rv, line, sizeof(line)), rv);
+        apr_file_printf(errfile, "apr_xlate_open(): %pm (%d)\n",
+                &rv, rv);
         exit(1);
     }
 #endif
 
     apr_signal(SIGINT, (void (*)(int)) interrupted);
     if (argc == 5) {
         if (strcmp(argv[1], "-c"))
             usage();
         rv = apr_file_open(&f, argv[2], APR_WRITE | APR_CREATE,
                            APR_OS_DEFAULT, cntxt);
         if (rv != APR_SUCCESS) {
-            char errmsg[120];
-
-            apr_file_printf(errfile, "Could not open passwd file %s for writing: %s\n",
-                    argv[2],
-                    apr_strerror(rv, errmsg, sizeof errmsg));
+            apr_file_printf(errfile, "Could not open passwd file %s for writing: %pm\n",
+                    argv[2], &rv);
             exit(1);
         }
         apr_cpystrn(user, argv[4], sizeof(user));
         apr_cpystrn(realm, argv[3], sizeof(realm));
         apr_file_printf(errfile, "Adding password for %s in realm %s.\n",
                     user, realm);
