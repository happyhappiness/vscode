    int use_strftime = 0;
    int use_localtime = 0;
    int now = 0;
    const char *szLogRoot;
    apr_file_t *f_stdin, *nLogFD = NULL, *nLogFDprev = NULL;
    apr_pool_t *pool;
    apr_getopt_t *opt;
    apr_status_t rv;
    char c;
    const char *optarg;
    char *ptr = NULL;

    apr_app_initialize(&argc, &argv, NULL);
    atexit(apr_terminate);

    apr_pool_create(&pool, NULL);
    apr_getopt_init(&opt, pool, argc, argv);
    while ((rv = apr_getopt(opt, "l", &c, &optarg)) == APR_SUCCESS) {
        switch (c) {
        case 'l':
            use_localtime = 1;
            break;
        }
    }

    if (rv != APR_EOF) {
        usage(argv[0], NULL /* specific error message already issued */ );
    }

    if (opt->ind + 2 != argc && opt->ind + 3 != argc) {
        usage(argv[0], "Incorrect number of arguments");
    }

    szLogRoot = argv[opt->ind++];

    ptr = strchr(argv[opt->ind], 'M');
    if (ptr) { /* rotation based on file size */
        if (*(ptr+1) == '\0') {
            sRotation = atoi(argv[opt->ind]) * 1048576;
        }
        if (sRotation == 0) {
            usage(argv[0], "Invalid rotation size parameter");
        }
    }
    else { /* rotation based on elapsed time */
        tRotation = atoi(argv[opt->ind]);
        if (tRotation <= 0) {
            usage(argv[0], "Invalid rotation time parameter");
        }
    }
    opt->ind++;

    if (opt->ind < argc) { /* have UTC offset */
        if (use_localtime) {
            usage(argv[0], "UTC offset parameter is not valid with -l");
        }
        utc_offset = atoi(argv[opt->ind]) * 60;
    }

    use_strftime = (strchr(szLogRoot, '%') != NULL);
    if (apr_file_open_stdin(&f_stdin, pool) != APR_SUCCESS) {
        fprintf(stderr, "Unable to open stdin\n");
        exit(1);
