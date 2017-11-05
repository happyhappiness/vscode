int main (int argc, const char * const argv[])
{
    char buf[BUFSIZE];
    apr_size_t nRead, nWrite;
    apr_file_t *f_stdin;
    apr_getopt_t *opt;
    apr_status_t rv;
    char c;
    const char *optarg;
    const char *err = NULL;

    apr_app_initialize(&argc, &argv, NULL);
    atexit(apr_terminate);

    config.sRotation = 0;
    config.tRotation = 0;
    config.utc_offset = 0;
    config.use_localtime = 0;
    config.use_strftime = 0;
    config.force_open = 0;
    config.verbose = 0;
    status.pool = NULL;
    status.pfile = NULL;
    status.pfile_prev = NULL;
    status.nLogFD = NULL;
    status.nLogFDprev = NULL;
    status.tLogEnd = 0;
    status.rotateReason = ROTATE_NONE;
    status.nMessCount = 0;

    apr_pool_create(&status.pool, NULL);
    apr_getopt_init(&opt, status.pool, argc, argv);
    while ((rv = apr_getopt(opt, "lL:ftv", &c, &optarg)) == APR_SUCCESS) {
        switch (c) {
        case 'l':
            config.use_localtime = 1;
            break;
        case 'L':
            config.linkfile = optarg;
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

    if (apr_file_open_stdin(&f_stdin, status.pool) != APR_SUCCESS) {
        fprintf(stderr, "Unable to open stdin\n");
        exit(1);
    }

    /*
     * Write out result of config parsing if verbose is set.
     */
    if (config.verbose) {
        dumpConfig(&config);
    }

    /*
     * Immediately open the logfile as we start, if we were forced
     * to do so via '-f'.
     */
    if (config.force_open) {
        doRotate(&config, &status);
    }

    for (;;) {
        nRead = sizeof(buf);
        rv = apr_file_read(f_stdin, buf, &nRead);
        if (rv != APR_SUCCESS) {
            exit(3);
        }
        checkRotate(&config, &status);
        if (status.rotateReason != ROTATE_NONE) {
            doRotate(&config, &status);
        }

        nWrite = nRead;
        rv = apr_file_write(status.nLogFD, buf, &nWrite);
        if (rv == APR_SUCCESS && nWrite != nRead) {
            /* buffer partially written, which for rotatelogs means we encountered
             * an error such as out of space or quota or some other limit reached;
             * try to write the rest so we get the real error code
             */
            apr_size_t nWritten = nWrite;

            nRead  = nRead - nWritten;
            nWrite = nRead;
            rv = apr_file_write(status.nLogFD, buf + nWritten, &nWrite);
        }
        if (nWrite != nRead) {
            char strerrbuf[120];
            apr_off_t cur_offset;

            cur_offset = 0;
            if (apr_file_seek(status.nLogFD, APR_CUR, &cur_offset) != APR_SUCCESS) {
                cur_offset = -1;
            }
            apr_strerror(rv, strerrbuf, sizeof strerrbuf);
            status.nMessCount++;
            apr_snprintf(status.errbuf, sizeof status.errbuf,
                         "Error %d writing to log file at offset %" APR_OFF_T_FMT ". "
                         "%10d messages lost (%s)\n",
                         rv, cur_offset, status.nMessCount, strerrbuf);
            nWrite = strlen(status.errbuf);
            apr_file_trunc(status.nLogFD, 0);
            if (apr_file_write(status.nLogFD, status.errbuf, &nWrite) != APR_SUCCESS) {
                fprintf(stderr, "Error writing to the file %s\n", status.filename);
                exit(2);
            }
        }
        else {
            status.nMessCount++;
        }
    }
    /* Of course we never, but prevent compiler warnings */
    return 0;
}