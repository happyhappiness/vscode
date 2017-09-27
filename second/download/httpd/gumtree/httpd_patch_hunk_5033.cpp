     }
 
     apr_file_open_stderr(&errfile, pool);
     rv = apr_getopt_init(&opt, pool, argc, argv);
 
     if (rv != APR_SUCCESS) {
-        apr_file_printf(errfile, "Error: apr_getopt_init failed."NL NL);
+        apr_file_printf(errfile, "Error: apr_getopt_init failed." NL NL);
         return 1;
     }
 
     if (argc <= 1) {
         usage();
         return 1;
