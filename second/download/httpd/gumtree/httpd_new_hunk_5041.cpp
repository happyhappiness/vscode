            usage(argv[0], err);
        }
    }

    config.use_strftime = (strchr(config.szLogRoot, '%') != NULL);

    if (config.use_strftime && config.num_files > 0) { 
        fprintf(stderr, "Cannot use -n with %% in filename\n");
        exit(1);
    }

    if (status.fileNum == -1 && config.num_files < 1) { 
        fprintf(stderr, "Invalid -n argument\n");
        exit(1);
    }

    if (apr_file_open_stdin(&f_stdin, status.pool) != APR_SUCCESS) {
        fprintf(stderr, "Unable to open stdin\n");
        exit(1);
    }

    if (apr_file_open_stdout(&f_stdout, status.pool) != APR_SUCCESS) {
