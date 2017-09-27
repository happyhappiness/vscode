#endif
    
    apr_signal(SIGINT, (void (*)(int)) interrupted);
    if (argc == 5) {
        if (strcmp(argv[1], "-c"))
            usage();
        rv = apr_file_open(&f, argv[2], APR_WRITE | APR_CREATE,
                           APR_OS_DEFAULT, cntxt);
        if (rv != APR_SUCCESS) {
            char errmsg[120];

            apr_file_printf(errfile, "Could not open passwd file %s for writing: %s\n",
                    argv[2],
                    apr_strerror(rv, errmsg, sizeof errmsg));
