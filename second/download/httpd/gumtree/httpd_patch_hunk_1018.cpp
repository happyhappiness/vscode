     }
 #endif
 
     apr_getopt_init(&opt, cntxt, argc, argv);
     while ((status = apr_getopt(opt, "n:c:t:T:p:v:kVhwix:y:z:C:H:P:A:g:X:de:Sq"
 #ifdef USE_SSL
-				"s"
+            "Z:f:"
 #endif
-				,&c, &optarg)) == APR_SUCCESS) {
+            ,&c, &optarg)) == APR_SUCCESS) {
 	switch (c) {
-	case 's':
-#ifdef USE_SSL
-        ssl = 1;
-        break;
-#else
-        fprintf(stderr, "SSL not compiled in; no https support\n");
-        exit(1);
-#endif
-	case 'n':
-	    requests = atoi(optarg);
-	    if (!requests) {
-		err("Invalid number of requests\n");
-	    }
-	    break;
-	case 'k':
-	    keepalive = 1;
-	    break;
-	case 'q':
-	    heartbeatres = 0;
-	    break;
-	case 'c':
-	    concurrency = atoi(optarg);
-	    break;
-	case 'i':
-	    if (posting == 1)
-		err("Cannot mix POST and HEAD\n");
-	    posting = -1;
-	    break;
-	case 'g':
-	    gnuplot = strdup(optarg);
-	    break;
-	case 'd':
-	    percentile = 0;
-	    break;
-	case 'e':
-	    csvperc = strdup(optarg);
-	    break;
-	case 'S':
-	    confidence = 0;
-	    break;
-	case 'p':
-	    if (posting != 0)
+            case 'n':
+                requests = atoi(optarg);
+                if (!requests) {
+                    err("Invalid number of requests\n");
+                }
+                break;
+            case 'k':
+                keepalive = 1;
+                break;
+            case 'q':
+                heartbeatres = 0;
+                break;
+            case 'c':
+                concurrency = atoi(optarg);
+                break;
+            case 'i':
+                if (posting == 1)
 		err("Cannot mix POST and HEAD\n");
+                posting = -1;
+                break;
+            case 'g':
+                gnuplot = strdup(optarg);
+                break;
+            case 'd':
+                percentile = 0;
+                break;
+            case 'e':
+                csvperc = strdup(optarg);
+                break;
+            case 'S':
+                confidence = 0;
+                break;
+            case 'p':
+                if (posting != 0)
+                    err("Cannot mix POST and HEAD\n");
+                if (0 == (r = open_postfile(optarg))) {
+                    posting = 1;
+                }
+                else if (postdata) {
+                    exit(r);
+                }
+                break;
+            case 'v':
+                verbosity = atoi(optarg);
+                break;
+            case 't':
+                tlimit = atoi(optarg);
+                requests = MAX_REQUESTS;    /* need to size data array on
+                                             * something */
+                break;
+            case 'T':
+                strcpy(content_type, optarg);
+                break;
+            case 'C':
+                cookie = apr_pstrcat(cntxt, "Cookie: ", optarg, "\r\n", NULL);
+                break;
+            case 'A':
+                /*
+                 * assume username passwd already to be in colon separated form.
+                 * Ready to be uu-encoded.
+                 */
+                while (apr_isspace(*optarg))
+                    optarg++;
+                if (apr_base64_encode_len(strlen(optarg)) > sizeof(tmp)) {
+                    err("Authentication credentials too long\n");
+                }
+                l = apr_base64_encode(tmp, optarg, strlen(optarg));
+                tmp[l] = '\0';
 
-	    if (0 == (r = open_postfile(optarg))) {
-		posting = 1;
-	    }
-	    else if (postdata) {
-		exit(r);
-	    }
-	    break;
-	case 'v':
-	    verbosity = atoi(optarg);
-	    break;
-	case 't':
-	    tlimit = atoi(optarg);
-	    requests = MAX_REQUESTS;	/* need to size data array on
-					 * something */
-	    break;
-	case 'T':
-	    strcpy(content_type, optarg);
-	    break;
-	case 'C':
-            cookie = apr_pstrcat(cntxt, "Cookie: ", optarg, "\r\n", NULL);
-	    break;
-	case 'A':
-	    /*
-	     * assume username passwd already to be in colon separated form.
-	     * Ready to be uu-encoded.
-	     */
-	    while (apr_isspace(*optarg))
-		optarg++;
-            if (apr_base64_encode_len(strlen(optarg)) > sizeof(tmp)) {
-                err("Authentication credentials too long\n");
-            }
-	    l = apr_base64_encode(tmp, optarg, strlen(optarg));
-	    tmp[l] = '\0';
-
-            auth = apr_pstrcat(cntxt, auth, "Authorization: Basic ", tmp,
-                               "\r\n", NULL);
-	    break;
-	case 'P':
-	    /*
-             * assume username passwd already to be in colon separated form.
-             */
-	    while (apr_isspace(*optarg))
+                auth = apr_pstrcat(cntxt, auth, "Authorization: Basic ", tmp,
+                                       "\r\n", NULL);
+                break;
+            case 'P':
+                /*
+                 * assume username passwd already to be in colon separated form.
+                 */
+                while (apr_isspace(*optarg))
 		optarg++;
-            if (apr_base64_encode_len(strlen(optarg)) > sizeof(tmp)) {
-                err("Proxy credentials too long\n");
-            }
-	    l = apr_base64_encode(tmp, optarg, strlen(optarg));
-	    tmp[l] = '\0';
+                if (apr_base64_encode_len(strlen(optarg)) > sizeof(tmp)) {
+                    err("Proxy credentials too long\n");
+                }
+                l = apr_base64_encode(tmp, optarg, strlen(optarg));
+                tmp[l] = '\0';
 
-            auth = apr_pstrcat(cntxt, auth, "Proxy-Authorization: Basic ",
-                               tmp, "\r\n", NULL);
-	    break;
-	case 'H':
-            hdrs = apr_pstrcat(cntxt, hdrs, optarg, "\r\n", NULL);
-	    break;
-	case 'w':
-	    use_html = 1;
-	    break;
-	    /*
-	     * if any of the following three are used, turn on html output
-	     * automatically
-	     */
-	case 'x':
-	    use_html = 1;
-	    tablestring = optarg;
-	    break;
-	case 'X':
-	    {
-		char *p;
+                auth = apr_pstrcat(cntxt, auth, "Proxy-Authorization: Basic ",
+                                       tmp, "\r\n", NULL);
+                break;
+            case 'H':
+                hdrs = apr_pstrcat(cntxt, hdrs, optarg, "\r\n", NULL);
+                break;
+            case 'w':
+                use_html = 1;
+                break;
 		/*
-                 * assume proxy-name[:port]
+                 * if any of the following three are used, turn on html output
+                 * automatically
                  */
-		if ((p = strchr(optarg, ':'))) {
-		    *p = '\0';
-		    p++;
-		    proxyport = atoi(p);
+            case 'x':
+                use_html = 1;
+                tablestring = optarg;
+                break;
+            case 'X':
+                {
+                    char *p;
+                    /*
+                     * assume proxy-name[:port]
+                     */
+                    if ((p = strchr(optarg, ':'))) {
+                        *p = '\0';
+                        p++;
+                        proxyport = atoi(p);
+                    }
+                    strcpy(proxyhost, optarg);
+                    isproxy = 1;
 		}
-		strcpy(proxyhost, optarg);
-		isproxy = 1;
-	    }
-	    break;
-	case 'y':
-	    use_html = 1;
-	    trstring = optarg;
-	    break;
-	case 'z':
-	    use_html = 1;
-	    tdstring = optarg;
-	    break;
-	case 'h':
-	    usage(argv[0]);
-	    break;
-	case 'V':
-	    copyright();
-	    return 0;
+                break;
+            case 'y':
+                use_html = 1;
+                trstring = optarg;
+                break;
+            case 'z':
+                use_html = 1;
+                tdstring = optarg;
+                break;
+            case 'h':
+                usage(argv[0]);
+                break;
+            case 'V':
+                copyright();
+                return 0;
+#ifdef USE_SSL
+            case 'Z':
+                ssl_cipher = strdup(optarg);
+                break;
+            case 'f':
+                if (strncasecmp(optarg, "ALL", 3) == 0) {
+                    meth = SSLv23_client_method();
+                } else if (strncasecmp(optarg, "SSL2", 4) == 0) {
+                    meth = SSLv2_client_method();
+                } else if (strncasecmp(optarg, "SSL3", 4) == 0) {
+                    meth = SSLv3_client_method();
+                } else if (strncasecmp(optarg, "TLS1", 4) == 0) {
+                    meth = TLSv1_client_method();
+                }
+                break;
+#endif
 	}
     }
 
     if (opt->ind != argc - 1) {
 	fprintf(stderr, "%s: wrong number of arguments\n", argv[0]);
 	usage(argv[0]);
