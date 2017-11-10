int main(int argc, const char *const argv[])
{
    apr_pool_t *pool;
    apr_status_t rv = APR_SUCCESS;
    apr_getopt_t *opt;
    const char *optarg;
    char ch;
    apr_file_t *infile;
    apr_dbm_t *outdbm;

    apr_app_initialize(&argc, &argv, NULL);
    atexit(apr_terminate);

    verbose = 0;
    format = NULL;
    input = NULL;
    output = NULL;

    apr_pool_create(&pool, NULL);

    if (argc) {
        shortname = apr_filepath_name_get(argv[0]);
    }
    else {
        shortname = "httxt2dbm";
    }

    apr_file_open_stderr(&errfile, pool);
    rv = apr_getopt_init(&opt, pool, argc, argv);

    if (rv != APR_SUCCESS) {
        apr_file_printf(errfile, "Error: apr_getopt_init failed."NL NL);
        return 1;
    }

    if (argc <= 1) {
        usage();
        return 1;
    }

    while ((rv = apr_getopt(opt, "vf::i::o::", &ch, &optarg)) == APR_SUCCESS) {
        switch (ch) {
        case 'v':
            if (verbose) {
                apr_file_printf(errfile, "Error: -v can only be passed once" NL NL);
                usage();
                return 1;
            }
            verbose = 1;
            break;
        case 'f':
            if (format) {
                apr_file_printf(errfile, "Error: -f can only be passed once" NL NL);
                usage();
                return 1;
            }
            format = apr_pstrdup(pool, optarg);
            break;
        case 'i':
            if (input) {
                apr_file_printf(errfile, "Error: -i can only be passed once" NL NL);
                usage();
                return 1;
            }
            input = apr_pstrdup(pool, optarg);
            break;
        case 'o':
            if (output) {
                apr_file_printf(errfile, "Error: -o can only be passed once" NL NL);
                usage();
                return 1;
            }
            output = apr_pstrdup(pool, optarg);
            break;
        }
    }

    if (rv != APR_EOF) {
        apr_file_printf(errfile, "Error: Parsing Arguments Failed" NL NL);
        usage();
        return 1;
    }

    if (!input) {
        apr_file_printf(errfile, "Error: No input file specified." NL NL);
        usage();
        return 1;
    }

    if (!output) {
        apr_file_printf(errfile, "Error: No output DBM specified." NL NL);
        usage();
        return 1;
    }

    if (!format) {
        format = "default";
    }

    if (verbose) {
        apr_file_printf(errfile, "DBM Format: %s"NL, format);
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
                        "Error: Cannot open input file '%s': (%d) %s" NL NL,
                         input, rv, apr_strerror(rv, errbuf, sizeof(errbuf)));
        return 1;
    }

    if (verbose) {
        apr_file_printf(errfile, "Input File: %s"NL, input);
    }

    rv = apr_dbm_open_ex(&outdbm, format, output, APR_DBM_RWCREATE,
                    APR_OS_DEFAULT, pool);

    if (APR_STATUS_IS_ENOTIMPL(rv)) {
        apr_file_printf(errfile,
                        "Error: The requested DBM Format '%s' is not available." NL NL,
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
        apr_file_printf(errfile, "Conversion Complete." NL);
    }

    return