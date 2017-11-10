int main (int argc, const char * const argv[])
{
    char buf[BUFSIZE];
    apr_size_t nRead, nWrite;
    apr_file_t *f_stdin;
    apr_file_t *f_stdout;
    apr_getopt_t *opt;
    apr_status_t rv;
    char c;
    const char *opt_arg;
    const char *err = NULL;
#if APR_FILES_AS_SOCKETS
    apr_pollfd_t pollfd = { 0 };
    apr_status_t pollret = APR_SUCCESS;
    int polltimeout;
#endif

    apr_app_initialize(&argc, &argv, NULL);
    atexit(apr_terminate);

    memset(&config, 0, sizeof config);
    memset(&status, 0, sizeof status);
    status.rotateReason = ROTATE_NONE;

    apr_pool_create(&status.pool, NULL);
    apr_getopt_init(&opt, status.pool, argc, argv);
#if APR_FILES_AS_SOCKETS
    while ((rv = apr_getopt(opt, "lL:p:ftvecn:", &c, &opt_arg)) == APR_SUCCESS) {
#else
    while ((rv = apr_getopt(opt, "lL:p:ftven:", &c, &opt_arg)) == APR_SUCCESS) {
#endif
        switch (c) {
        case 'l':
            config.use_localtime = 1;
            break;
        case 'L':
            config.linkfile = opt_arg;
            break;
        case 'p':
            config.postrotate_prog = opt_arg;
            break;
        case 'f':
            config.force_open = 1;
            break;
        case 't':
            config.truncate = 1;
            break;
        case 'v':
            config.verbose = 1;
            break;
        case 'e':
            config.echo = 1;
            break;
#if APR_FILES_AS_SOCKETS
        case 'c':
            config.create_empty = 1;
            break;
#endif
        case 'n':
            config.num_files = atoi(opt_arg);
            status.fileNum = -1;
            break;
        }
    }

    if (rv != APR_EOF) {
        usage(argv[0], NULL /* specific error message already issued */ );
    }

    /*
     * After the initial flags we need 2 to 4 arguments,
     * the file name, either the rotation interval time or size
     * or both of them, and optionally the UTC offset.
     */
    if ((argc - opt->ind < 2) || (argc - opt->ind > 4) ) {
        usage(argv[0], "Incorrect number of arguments");
    }

    config.szLogRoot = argv[opt->ind++];

    /* Read in the remaining flags, namely time, size and UTC offset. */
    for(; opt->ind < argc; opt->ind++) {
        if ((err = get_time_or_size(&config, argv[opt->ind],
                                    opt->ind < argc - 1 ? 0 : 1)) != NULL) {
            usage(argv[0], err);
        }
    }

    config.use_strftime = (strchr(config.szLogRoot, '%') != NULL);

    if (config.use_strftime && config.num_files > 0) { 
        fprintf(stderr, "Cannot use -n with %% in filename\n");
        exit(1);
    }

    if (status.fileNum == -1 && config.num_files < 1) { 
        fprintf(stderr, "Invalid -n argument\n");
        exit(1);
    }

    if (apr_file_open_stdin(&f_stdin, status.pool) != APR_SUCCESS) {
        fprintf(stderr, "Unable to open stdin\n");
        exit(1);
    }

    if (apr_file_open_stdout(&f_stdout, status.pool) != APR_SUCCESS) {
        fprintf(stderr, "Unable to open stdout\n");
        exit(1);
    }

    /*
     * Write out result of config parsing if verbose is set.
     */
    if (config.verbose) {
        dumpConfig(&config);
    }

#if APR_FILES_AS_SOCKETS
    if (config.create_empty && config.tRotation) {
        pollfd.p = status.pool;
        pollfd.desc_type = APR_POLL_FILE;
        pollfd.reqevents = APR_POLLIN;
        pollfd.desc.f = f_stdin;
    }
#endif

    /*
     * Immediately open the logfile as we start, if we were forced
     * to do so via '-f'.
     */
    if (config.force_open) {
        doRotate(&config, &status);
    }

    for (;;) {
        nRead = sizeof(buf);
#if APR_FILES_AS_SOCKETS
        if (config.create_empty && config.tRotation) {
            polltimeout = status.tLogEnd ? status.tLogEnd - get_now(&config) : config.tRotation;
            if (polltimeout <= 0) {
                pollret = APR_TIMEUP;
            }
            else {
                pollret = apr_poll(&pollfd, 1, &pollret, apr_time_from_sec(polltimeout));
            }
        }
        if (pollret == APR_SUCCESS) {
            rv = ap