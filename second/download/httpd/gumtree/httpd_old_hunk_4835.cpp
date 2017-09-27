    if (!(mask & APHTP_NOFILE)) {
        existing_file = exists(pwfilename, pool);
        if (existing_file) {
            /*
             * Check that this existing file is readable and writable.
             */
            if (!accessible(pool, pwfilename, APR_READ | APR_APPEND)) {
                apr_file_printf(errfile, "%s: cannot open file %s for "
                                "read/write access" NL, argv[0], pwfilename);
                exit(ERR_FILEPERM);
            }
        }
        else {
