         fprintf(stderr, "apr_base64init_ebcdic()->%d\n", status);
         exit(1);
     }
 #endif
 
     apr_getopt_init(&opt, cntxt, argc, argv);
-    while ((status = apr_getopt(opt, "n:c:t:T:p:v:kVhwix:y:z:C:H:P:A:g:X:de:Sq"
+    while ((status = apr_getopt(opt, "n:c:t:b:T:p:v:rkVhwix:y:z:C:H:P:A:g:X:de:Sq"
 #ifdef USE_SSL
             "Z:f:"
 #endif
             ,&c, &optarg)) == APR_SUCCESS) {
         switch (c) {
             case 'n':
                 requests = atoi(optarg);
-                if (!requests) {
+                if (requests <= 0) {
                     err("Invalid number of requests\n");
                 }
                 break;
             case 'k':
                 keepalive = 1;
                 break;
             case 'q':
                 heartbeatres = 0;
                 break;
             case 'c':
                 concurrency = atoi(optarg);
                 break;
+            case 'b':
+                windowsize = atoi(optarg);
+                break;
             case 'i':
                 if (posting == 1)
                 err("Cannot mix POST and HEAD\n");
                 posting = -1;
                 break;
             case 'g':
