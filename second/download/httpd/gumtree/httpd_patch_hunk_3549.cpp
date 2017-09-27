     if (status) {
         fprintf(stderr, "apr_base64init_ebcdic()->%d\n", status);
         exit(1);
     }
 #endif
 
+    myhost = NULL; /* 0.0.0.0 or :: */
+
     apr_getopt_init(&opt, cntxt, argc, argv);
-    while ((status = apr_getopt(opt, "n:c:t:b:T:p:u:v:rkVhwix:y:z:C:H:P:A:g:X:de:Sq"
+    while ((status = apr_getopt(opt, "n:c:t:b:T:p:u:v:rkVhwix:y:z:C:H:P:A:g:X:de:SqB:"
 #ifdef USE_SSL
             "Z:f:"
 #endif
-            ,&c, &optarg)) == APR_SUCCESS) {
+            ,&c, &opt_arg)) == APR_SUCCESS) {
         switch (c) {
             case 'n':
-                requests = atoi(optarg);
+                requests = atoi(opt_arg);
                 if (requests <= 0) {
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
-                concurrency = atoi(optarg);
+                concurrency = atoi(opt_arg);
                 break;
             case 'b':
-                windowsize = atoi(optarg);
+                windowsize = atoi(opt_arg);
                 break;
             case 'i':
                 if (method != NO_METH)
                     err("Cannot mix HEAD with other methods\n");
                 method = HEAD;
                 break;
             case 'g':
-                gnuplot = strdup(optarg);
+                gnuplot = strdup(opt_arg);
                 break;
             case 'd':
                 percentile = 0;
                 break;
             case 'e':
-                csvperc = strdup(optarg);
+                csvperc = strdup(opt_arg);
                 break;
             case 'S':
                 confidence = 0;
                 break;
             case 'p':
                 if (method != NO_METH)
                     err("Cannot mix POST with other methods\n");
-                if ((status = open_postfile(optarg)) != APR_SUCCESS) {
+                if (open_postfile(opt_arg) != APR_SUCCESS) {
                     exit(1);
                 }
                 method = POST;
                 send_body = 1;
                 break;
             case 'u':
                 if (method != NO_METH)
                     err("Cannot mix PUT with other methods\n");
-                if ((status = open_postfile(optarg)) != APR_SUCCESS) {
+                if (open_postfile(opt_arg) != APR_SUCCESS) {
                     exit(1);
                 }
                 method = PUT;
                 send_body = 1;
                 break;
             case 'r':
                 recverrok = 1;
                 break;
             case 'v':
-                verbosity = atoi(optarg);
+                verbosity = atoi(opt_arg);
                 break;
             case 't':
-                tlimit = atoi(optarg);
+                tlimit = atoi(opt_arg);
                 requests = MAX_REQUESTS;    /* need to size data array on
                                              * something */
                 break;
             case 'T':
-                strcpy(content_type, optarg);
+                strcpy(content_type, opt_arg);
                 break;
             case 'C':
-                cookie = apr_pstrcat(cntxt, "Cookie: ", optarg, "\r\n", NULL);
+                cookie = apr_pstrcat(cntxt, "Cookie: ", opt_arg, "\r\n", NULL);
                 break;
             case 'A':
                 /*
                  * assume username passwd already to be in colon separated form.
                  * Ready to be uu-encoded.
                  */
-                while (apr_isspace(*optarg))
-                    optarg++;
-                if (apr_base64_encode_len(strlen(optarg)) > sizeof(tmp)) {
+                while (apr_isspace(*opt_arg))
+                    opt_arg++;
+                if (apr_base64_encode_len(strlen(opt_arg)) > sizeof(tmp)) {
                     err("Authentication credentials too long\n");
                 }
-                l = apr_base64_encode(tmp, optarg, strlen(optarg));
+                l = apr_base64_encode(tmp, opt_arg, strlen(opt_arg));
                 tmp[l] = '\0';
 
                 auth = apr_pstrcat(cntxt, auth, "Authorization: Basic ", tmp,
                                        "\r\n", NULL);
                 break;
             case 'P':
                 /*
                  * assume username passwd already to be in colon separated form.
                  */
-                while (apr_isspace(*optarg))
-                optarg++;
-                if (apr_base64_encode_len(strlen(optarg)) > sizeof(tmp)) {
+                while (apr_isspace(*opt_arg))
+                opt_arg++;
+                if (apr_base64_encode_len(strlen(opt_arg)) > sizeof(tmp)) {
                     err("Proxy credentials too long\n");
                 }
-                l = apr_base64_encode(tmp, optarg, strlen(optarg));
+                l = apr_base64_encode(tmp, opt_arg, strlen(opt_arg));
                 tmp[l] = '\0';
 
                 auth = apr_pstrcat(cntxt, auth, "Proxy-Authorization: Basic ",
                                        tmp, "\r\n", NULL);
                 break;
             case 'H':
-                hdrs = apr_pstrcat(cntxt, hdrs, optarg, "\r\n", NULL);
+                hdrs = apr_pstrcat(cntxt, hdrs, opt_arg, "\r\n", NULL);
                 /*
                  * allow override of some of the common headers that ab adds
                  */
-                if (strncasecmp(optarg, "Host:", 5) == 0) {
+                if (strncasecmp(opt_arg, "Host:", 5) == 0) {
                     opt_host = 1;
-                } else if (strncasecmp(optarg, "Accept:", 7) == 0) {
+                } else if (strncasecmp(opt_arg, "Accept:", 7) == 0) {
                     opt_accept = 1;
-                } else if (strncasecmp(optarg, "User-Agent:", 11) == 0) {
+                } else if (strncasecmp(opt_arg, "User-Agent:", 11) == 0) {
                     opt_useragent = 1;
                 }
                 break;
             case 'w':
                 use_html = 1;
                 break;
                 /*
                  * if any of the following three are used, turn on html output
                  * automatically
                  */
             case 'x':
                 use_html = 1;
-                tablestring = optarg;
+                tablestring = opt_arg;
                 break;
             case 'X':
                 {
                     char *p;
                     /*
                      * assume proxy-name[:port]
                      */
-                    if ((p = strchr(optarg, ':'))) {
+                    if ((p = strchr(opt_arg, ':'))) {
                         *p = '\0';
                         p++;
                         proxyport = atoi(p);
                     }
-                    strcpy(proxyhost, optarg);
+                    strcpy(proxyhost, opt_arg);
                     isproxy = 1;
                 }
                 break;
             case 'y':
                 use_html = 1;
-                trstring = optarg;
+                trstring = opt_arg;
                 break;
             case 'z':
                 use_html = 1;
-                tdstring = optarg;
+                tdstring = opt_arg;
                 break;
             case 'h':
                 usage(argv[0]);
                 break;
             case 'V':
                 copyright();
                 return 0;
+            case 'B':
+                myhost = apr_pstrdup(cntxt, opt_arg);
+                break;
 #ifdef USE_SSL
             case 'Z':
-                ssl_cipher = strdup(optarg);
+                ssl_cipher = strdup(opt_arg);
                 break;
             case 'f':
-                if (strncasecmp(optarg, "ALL", 3) == 0) {
+                if (strncasecmp(opt_arg, "ALL", 3) == 0) {
                     meth = SSLv23_client_method();
-                } else if (strncasecmp(optarg, "SSL2", 4) == 0) {
+#ifndef OPENSSL_NO_SSL2
+                } else if (strncasecmp(opt_arg, "SSL2", 4) == 0) {
                     meth = SSLv2_client_method();
-                } else if (strncasecmp(optarg, "SSL3", 4) == 0) {
+#endif
+                } else if (strncasecmp(opt_arg, "SSL3", 4) == 0) {
                     meth = SSLv3_client_method();
-                } else if (strncasecmp(optarg, "TLS1", 4) == 0) {
+                } else if (strncasecmp(opt_arg, "TLS1", 4) == 0) {
                     meth = TLSv1_client_method();
                 }
                 break;
 #endif
         }
     }
