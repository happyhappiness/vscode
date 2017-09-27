     int use_strftime = 0;
     int use_localtime = 0;
     int now = 0;
     const char *szLogRoot;
     apr_file_t *f_stdin, *nLogFD = NULL, *nLogFDprev = NULL;
     apr_pool_t *pool;
+    apr_getopt_t *opt;
+    apr_status_t rv;
+    char c;
+    const char *optarg;
     char *ptr = NULL;
-    int argBase = 0;
-    int argFile = 1;
-    int argIntv = 2;
-    int argOffset = 3;
 
     apr_app_initialize(&argc, &argv, NULL);
     atexit(apr_terminate);
 
     apr_pool_create(&pool, NULL);
-    if ((argc > 2) && (strcmp(argv[1], "-l") == 0)) {
-        argBase++;
-        argFile += argBase;
-        argIntv += argBase;
-        argOffset += argBase;
-        use_localtime = 1;
-    }
-    if (argc < (argBase + 3) || argc > (argBase + 4)) {
-        fprintf(stderr,
-                "Usage: %s [-l] <logfile> <rotation time in seconds> "
-                "[offset minutes from UTC] or <rotation size in megabytes>\n\n",
-                argv[0]);
-#ifdef OS2
-        fprintf(stderr,
-                "Add this:\n\nTransferLog \"|%s.exe /some/where 86400\"\n\n",
-                argv[0]);
-#else
-        fprintf(stderr,
-                "Add this:\n\nTransferLog \"|%s /some/where 86400\"\n\n",
-                argv[0]);
-        fprintf(stderr,
-                "or \n\nTransferLog \"|%s /some/where 5M\"\n\n", argv[0]);
-#endif
-        fprintf(stderr,
-                "to httpd.conf. The generated name will be /some/where.nnnn "
-                "where nnnn is the\nsystem time at which the log nominally "
-                "starts (N.B. if using a rotation time,\nthe time will always "
-                "be a multiple of the rotation time, so you can synchronize\n"
-                "cron scripts with it). At the end of each rotation time or "
-                "when the file size\nis reached a new log is started.\n");
-        exit(1);
+    apr_getopt_init(&opt, pool, argc, argv);
+    while ((rv = apr_getopt(opt, "l", &c, &optarg)) == APR_SUCCESS) {
+        switch (c) {
+        case 'l':
+            use_localtime = 1;
+            break;
+        }
+    }
+
+    if (rv != APR_EOF) {
+        usage(argv[0], NULL /* specific error message already issued */ );
+    }
+
+    if (opt->ind + 2 != argc && opt->ind + 3 != argc) {
+        usage(argv[0], "Incorrect number of arguments");
     }
 
-    szLogRoot = argv[argFile];
+    szLogRoot = argv[opt->ind++];
 
-    ptr = strchr(argv[argIntv], 'M');
-    if (ptr) {
+    ptr = strchr(argv[opt->ind], 'M');
+    if (ptr) { /* rotation based on file size */
         if (*(ptr+1) == '\0') {
-            sRotation = atoi(argv[argIntv]) * 1048576;
+            sRotation = atoi(argv[opt->ind]) * 1048576;
         }
         if (sRotation == 0) {
-            fprintf(stderr, "Invalid rotation size parameter\n");
-            exit(1);
+            usage(argv[0], "Invalid rotation size parameter");
         }
     }
-    else {
-        if (argc >= (argBase + 4)) {
-            utc_offset = atoi(argv[argOffset]) * 60;
-        }
-        tRotation = atoi(argv[argIntv]);
+    else { /* rotation based on elapsed time */
+        tRotation = atoi(argv[opt->ind]);
         if (tRotation <= 0) {
-            fprintf(stderr, "Rotation time must be > 0\n");
-            exit(6);
+            usage(argv[0], "Invalid rotation time parameter");
+        }
+    }
+    opt->ind++;
+
+    if (opt->ind < argc) { /* have UTC offset */
+        if (use_localtime) {
+            usage(argv[0], "UTC offset parameter is not valid with -l");
         }
+        utc_offset = atoi(argv[opt->ind]) * 60;
     }
 
     use_strftime = (strchr(szLogRoot, '%') != NULL);
     if (apr_file_open_stdin(&f_stdin, pool) != APR_SUCCESS) {
         fprintf(stderr, "Unable to open stdin\n");
         exit(1);
