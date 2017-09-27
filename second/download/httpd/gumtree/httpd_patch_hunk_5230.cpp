     proxyhost = "";
     hdrs = "";
 
     apr_app_initialize(&argc, &argv, NULL);
     atexit(apr_terminate);
     apr_pool_create(&cntxt, NULL);
+    apr_pool_abort_set(abort_on_oom, cntxt);
 
 #ifdef NOT_ASCII
     status = apr_xlate_open(&to_ascii, "ISO-8859-1", APR_DEFAULT_CHARSET, cntxt);
     if (status) {
         fprintf(stderr, "apr_xlate_open(to ASCII)->%d\n", status);
         exit(1);
