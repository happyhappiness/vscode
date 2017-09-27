                         format);
        return 1;
    }

    if (rv != APR_SUCCESS) {
        apr_file_printf(errfile,
                        "Error: Cannot open output DBM '%s': (%d) %s" NL NL,
                         output, rv, apr_strerror(rv, errbuf, sizeof(errbuf)));
        return 1;
    }

    if (verbose) {
        apr_file_printf(errfile, "DBM File: %s"NL, output);
    }

    rv = to_dbm(outdbm, infile, pool);

    if (rv != APR_SUCCESS) {
        apr_file_printf(errfile,
                        "Error: Converting to DBM: (%d) %s" NL NL,
                         rv, apr_strerror(rv, errbuf, sizeof(errbuf)));
        return 1;
    }

    apr_dbm_close(outdbm);

    if (verbose) {
