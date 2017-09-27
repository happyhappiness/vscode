
    if (!format) {
        format = "default";
    }

    if (verbose) {
        apr_file_printf(errfile, "DBM Format: %s" NL, format);
    }

    if (!strcmp(input, "-")) {
        rv = apr_file_open_stdin(&infile, pool);
    }
    else {
        rv = apr_file_open(&infile, input, APR_READ|APR_BUFFERED,
                           APR_OS_DEFAULT, pool);
    }

    if (rv != APR_SUCCESS) {
        apr_file_printf(errfile,
                        "Error: Cannot open input file '%s': (%d) %pm" NL NL,
                         input, rv, &rv);
        return 1;
    }

    if (verbose) {
        apr_file_printf(errfile, "Input File: %s" NL, input);
    }

    rv = apr_dbm_open_ex(&outdbm, format, output, APR_DBM_RWCREATE,
                    APR_OS_DEFAULT, pool);

    if (APR_STATUS_IS_ENOTIMPL(rv)) {
