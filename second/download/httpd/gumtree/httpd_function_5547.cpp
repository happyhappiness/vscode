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
    while ((rv = apr_getopt(opt, "lL:p:ftvec", &c, &opt_arg)) == APR_SUCCESS) {
#else
    while ((rv = apr_getopt(opt, "lL:p:ftve", &c, &opt_arg)) == APR_SUCCESS) {
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
            rv = apr_file_read(f_stdin, buf, &nRead);
            if (APR_STATUS_IS_EOF(rv)) {
                break;
            }
            else if (rv != APR_SUCCESS) {
                exit(3);
            }
        }
        else if (pollret == APR_TIMEUP) {
            *buf = 0;
            nRead = 0;
        }
        else {
            fprintf(stderr, "Unable to poll stdin\n");
            exit(5);
        }
#else /* APR_FILES_AS_SOCKETS */
        rv = apr_file_read(f_stdin, buf, &nRead);
        if (APR_STATUS_IS_EOF(rv)) {
            break;
        }
        else if (rv != APR_SUCCESS) {
            exit(3);
        }
#endif /* APR_FILES_AS_SOCKETS */
        checkRotate(&config, &status);
        if (status.rotateReason != ROTATE_NONE) {
            doRotate(&config, &status);
        }

        nWrite = nRead;
        rv = apr_file_write(status.current.fd, buf, &nWrite);
        if (rv == APR_SUCCESS && nWrite != nRead) {
            /* buffer partially written, which for rotatelogs means we encountered
             * an error such as out of space or quota or some other limit reached;
             * try to write the rest so we get the real error code
             */
            apr_size_t nWritten = nWrite;

            nRead  = nRead - nWritten;
            nWrite = nRead;
            rv = apr_file_write(status.current.fd, buf + nWritten, &nWrite);
        }
        if (nWrite != nRead) {
            char strerrbuf[120];
            apr_off_t cur_offset;

            cur_offset = 0;
            if (apr_file_seek(status.current.fd, APR_CUR, &cur_offset) != APR_SUCCESS) {
                cur_offset = -1;
            }
            apr_strerror(rv, strerrbuf, sizeof strerrbuf);
            status.nMessCount++;
            apr_snprintf(status.errbuf, sizeof status.errbuf,
                         "Error %d writing to log file at offset %" APR_OFF_T_FMT ". "
                         "%10d messages lost (%s)\n",
                         rv, cur_offset, status.nMessCount, strerrbuf);
            nWrite = strlen(status.errbuf);
            apr_file_trunc(status.current.fd, 0);
            if (apr_file_write(status.current.fd, status.errbuf, &nWrite) != APR_SUCCESS) {
                fprintf(stderr, "Error writing to the file %s\n", status.current.name);
                exit(2);
            }
        }
        else {
            status.nMessCount++;
        }
        if (config.echo) {
            if (apr_file_write_full(f_stdout, buf, nRead, &nWrite)) {
                fprintf(stderr, "Unable to write to stdout\n");
                exit(4);
            }
        }
    }

    return 0; /* reached only at stdin EOF. */
}