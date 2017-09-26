    char realm[MAX_STRING_LEN];
    char line[MAX_STRING_LEN];
    char l[MAX_STRING_LEN];
    char w[MAX_STRING_LEN];
    char x[MAX_STRING_LEN];
    int found;

    apr_app_initialize(&argc, &argv, NULL);
    atexit(terminate);
    apr_pool_create(&cntxt, NULL);
    apr_file_open_stderr(&errfile, cntxt);

#if APR_CHARSET_EBCDIC
    rv = apr_xlate_open(&to_ascii, "ISO-8859-1", APR_DEFAULT_CHARSET, cntxt);
    if (rv) {
        apr_file_printf(errfile, "apr_xlate_open(): %s (%d)\n",
                apr_strerror(rv, line, sizeof(line)), rv);
        exit(1);
    }
#endif

    apr_signal(SIGINT, (void (*)(int)) interrupted);
    if (argc == 5) {
        if (strcmp(argv[1], "-c"))
            usage();
        rv = apr_file_open(&f, argv[2], APR_WRITE | APR_CREATE,
                           APR_OS_DEFAULT, cntxt);
