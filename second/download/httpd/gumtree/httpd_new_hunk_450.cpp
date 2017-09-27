
    if (apr_file_mktemp(&tfp, dirname, 0, cntxt) != APR_SUCCESS) {
        apr_file_printf(errfile, "Could not open temp file %s.\n", dirname);
        exit(1);
    }

    if (apr_file_open(&f, argv[1], APR_READ, APR_OS_DEFAULT, cntxt) != APR_SUCCESS) {
        apr_file_printf(errfile,
                "Could not open passwd file %s for reading.\n", argv[1]);
        apr_file_printf(errfile, "Use -c option to create new one.\n");
        cleanup_tempfile_and_exit(1);
    }
    apr_cpystrn(user, argv[3], sizeof(user));
