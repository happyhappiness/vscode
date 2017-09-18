(*mask & (APHTP_NEWFILE | APHTP_NOFILE)) {
        apr_file_printf(errfile, "%s: -c and -n options conflict\n", argv[0]);
        exit(ERR_SYNTAX);
    };