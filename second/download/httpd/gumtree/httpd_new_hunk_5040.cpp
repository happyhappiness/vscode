        apr_strftime(newlog.name, &rs, sizeof(newlog.name), config->szLogRoot, &e);
    }
    else {
        if (config->truncate) {
            apr_snprintf(newlog.name, sizeof(newlog.name), "%s", config->szLogRoot);
        }
        else if (config->num_files > 0) { 
            if (status->fileNum == -1 || status->fileNum == (config->num_files - 1)) {
                thisLogNum = 0;
                apr_snprintf(newlog.name, sizeof(newlog.name), "%s", config->szLogRoot);
            }
            else { 
                thisLogNum = status->fileNum + 1;
                apr_snprintf(newlog.name, sizeof(newlog.name), "%s.%d", config->szLogRoot, thisLogNum);
            }
        }
        else {
            apr_snprintf(newlog.name, sizeof(newlog.name), "%s.%010d", config->szLogRoot,
                         tLogStart);
        }
    }
    apr_pool_create(&newlog.pool, status->pool);
    if (config->verbose) {
        fprintf(stderr, "Opening file %s\n", newlog.name);
    }
    rv = apr_file_open(&newlog.fd, newlog.name, APR_WRITE | APR_CREATE | APR_APPEND
                       | (config->truncate || (config->num_files > 0 && status->current.fd) ? APR_TRUNCATE : 0), 
                       APR_OS_DEFAULT, newlog.pool);
    if (rv == APR_SUCCESS) {
        /* Handle post-rotate processing. */
        post_rotate(newlog.pool, &newlog, config, status);

        status->fileNum = thisLogNum;
        /* Close out old (previously 'current') logfile, if any. */
        if (status->current.fd) {
            close_logfile(config, &status->current);
        }

        /* New log file is now 'current'. */
