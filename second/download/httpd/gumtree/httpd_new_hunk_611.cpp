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
