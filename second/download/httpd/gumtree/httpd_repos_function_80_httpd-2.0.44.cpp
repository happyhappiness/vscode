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
	usage(ar