 
     if (opt->ind != argc - 1) {
         fprintf(stderr, "%s: wrong number of arguments\n", argv[0]);
         usage(argv[0]);
     }
 
+    if (method == NO_METH) {
+        method = GET;
+    }
+
     if (parse_url(apr_pstrdup(cntxt, opt->argv[opt->ind++]))) {
         fprintf(stderr, "%s: invalid URL\n", argv[0]);
         usage(argv[0]);
     }
 
     if ((concurrency < 0) || (concurrency > MAX_CONCURRENCY)) {
