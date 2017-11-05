int main(int argc, const char * const argv[])
{
    int r, l;
    char tmp[1024];
    apr_status_t status;
    apr_getopt_t *opt;
    const char *optarg;
    char c;

    /* table defaults  */
    tablestring = "";
    trstring = "";
    tdstring = "bgcolor=white";
    cookie = "";
    auth = "";
    proxyhost[0] = '\0';
    hdrs = "";

    apr_app_initialize(&argc, &argv, NULL);
    atexit(apr_terminate);
    apr_pool_create(&cntxt, NULL);

#ifdef NOT_ASCII
    status = apr_xlate_open(&to_ascii, "ISO8859-1", APR_DEFAULT_CHARSET, cntxt);
    if (status) {
	fprintf(stderr, "apr_xlate_open(to ASCII)->%d\n", status);
	exit(1);
    }
    status = apr_xlate_open(&from_ascii, APR_DEFAULT_CHARSET, "ISO8859-1", cntxt);
    if (status) {
	fprintf(stderr, "apr_xlate_open(from ASCII)->%d\n", status);
	exit(1);
    }
    status = apr_base64init_ebcdic(to_ascii, from_ascii);
    if (status) {
	fprintf(stderr, "apr_base64init_ebcdic()->%d\n", status);
	exit(1);
    }
#endif

    apr_getopt_init(&opt, cntxt, argc, argv);
    while ((status = apr_getopt(opt, "n:c:t:T:p:v:kVhwix:y:z:C:H:P:A:g:X:de:Sq"
#ifdef USE_SSL
				"s"
#endif
				,&c, &optarg)) == APR_SUCCESS) {
	switch (c) {
	case 's':
#ifdef USE_SSL
        ssl = 1;
        break;
#else
        fprintf(stderr, "SSL not compiled in; no https support\n");
        exit(1);
#endif
	case 'n':
	    requests = atoi(optarg);
	    if (!requests) {
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
	case 'i':
	    if (posting == 1)
		err("Cannot mix POST and HEAD\n");
	    posting = -1;
	    break;
	case 'g':
	    gnuplot = strdup(optarg);
	    break;
	case 'd':
	    percentile = 0;
	    break;
	case 'e':
	    csvperc = strdup(optarg);
	    break;
	case 'S':
	    confidence = 0;
	    break;
	case 'p':
	    if (posting != 0)
		err("Cannot mix POST and HEAD\n");

	    if (0 == (r = open_postfile(optarg))) {
		posting = 1;
	    }
	    else if (postdata) {
		exit(r);
	    }
	    break;
	case 'v':
	    verbosity = atoi(optarg);
	    break;
	case 't':
	    tlimit = atoi(optarg);
	    requests = MAX_REQUESTS;	/* need to size data array on
					 * something */
	    break;
	case 'T':
	    strcpy(content_type, optarg);
	    break;
	case 'C':
            cookie = apr_pstrcat(cntxt, "Cookie: ", optarg, "\r\n", NULL);
	    break;
	case 'A':
	    /*
	     * assume username passwd already to be in colon separated form.
	     * Ready to be uu-encoded.
	     */
	    while (apr_isspace(*optarg))
		optarg++;
            if (apr_base64_encode_len(strlen(optarg)) > sizeof(tmp)) {
                err("Authentication credentials too long\n");
            }
	    l = apr_base64_encode(tmp, optarg, strlen(optarg));
	    tmp[l] = '\0';

            auth = apr_pstrcat(cntxt, auth, "Authorization: Basic ", tmp,
                               "\r\n", NULL);
	    break;
	case 'P':
	    /*
             * assume username passwd already to be in colon separated form.
             */
	    while (apr_isspace(*optarg))
		optarg++;
            if (apr_base64_encode_len(strlen(optarg)) > sizeof(tmp)) {
                err("Proxy credentials too long\n");
            }
	    l = apr_base64_encode(tmp, optarg, strlen(optarg));
	    tmp[l] = '\0';

            auth = apr_pstrcat(cntxt, auth, "Proxy-Authorization: Basic ",
                               tmp, "\r\n", NULL);
	    break;
	case 'H':
            hdrs = apr_pstrcat(cntxt, hdrs, optarg, "\r\n", NULL);
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
	    tablestring = optarg;
	    break;
	case 'X':
	    {
		char *p;
		/*
                 * assume proxy-name[:port]
                 */
		if ((p = strchr(optarg, ':'))) {
		    *p = '\0';
		    p++;
		    proxyport = atoi(p);
		}
		strcpy(proxyhost, optarg);
		isproxy = 1;
	    }
	    break;
	case 'y':
	    use_html = 1;
	    trstring = optarg;
	    break;
	case 'z':
	    use_html = 1;
	    tdstring = optarg;
	    break;
	case 'h':
	    usage(argv[0]);
	    break;
	case 'V':
	    copyright();
	    return 0;
	}
    }

    if (opt->ind != argc - 1) {
	fprintf(stderr, "%s: wrong number of arguments\n", argv[0]);
	usage(argv[0]);
    }

    if (parse_url(apr_pstrdup(cntxt, opt->argv[opt->ind++]))) {
	fprintf(stderr, "%s: invalid URL\n", argv[0]);
	usage(argv[0]);
    }

    if ((concurrency < 0) || (concurrency > MAX_CONCURRENCY)) {
       fprintf(stderr, "%s: Invalid Concurrency [Range 0..%d]\n",
                argv[0], MAX_CONCURRENCY);
        usage(argv[0]);
    }

    if ((heartbeatres) && (requests > 150)) {
	heartbeatres = requests / 10;	/* Print line every 10% of requests */
	if (heartbeatres < 100)
	    heartbeatres = 100;	/* but never more often than once every 100
				 * connections. */
    }
    else
	heartbeatres = 0;

#ifdef USE_SSL
#ifdef RSAREF
    R_malloc_init();
#else
    CRYPTO_malloc_init();
#endif
    SSL_load_error_strings();
    SSL_library_init();
    bio_out=BIO_new_fp(stdout,BIO_NOCLOSE);
    bio_err=BIO_new_fp(stderr,BIO_NOCLOSE);

    /* TODO: Allow force SSLv2_client_method() (TLSv1?) */
    if (!(ctx = SSL_CTX_new(SSLv23_client_method()))) {
	fprintf(stderr, "Could not init SSL CTX");
	ERR_print_errors_fp(stderr);
	exit(1);
    }
    SSL_CTX_set_options(ctx, SSL_OP_ALL);
#ifdef USE_THREADS
    ssl_util_thread_setup(cntxt);
#endif
#endif
#ifdef SIGPIPE
    apr_signal(SIGPIPE, SIG_IGN);       /* Ignore writes to connections that
					 * have been closed at the other end. */
#endif
    copyright();
    test();
    apr_pool_destroy(cntxt);

    return 0;
}