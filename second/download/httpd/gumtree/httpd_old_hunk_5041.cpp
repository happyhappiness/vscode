            usage(argv[0], err);
        }
    }

    config.use_strftime = (strchr(config.szLogRoot, '%') != NULL);

    if (apr_file_open_stdin(&f_stdin, status.pool) != APR_SUCCESS) {
        fprintf(stderr, "Unable to open stdin\n");
        exit(1);
    }

    if (apr_file_open_stdout(&f_stdout, status.pool) != APR_SUCCESS) {
