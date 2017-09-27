    if (config->use_strftime) {
        apr_time_t tNow = apr_time_from_sec(tLogStart);
        apr_time_exp_t e;
        apr_size_t rs;

        apr_time_exp_gmt(&e, tNow);
        apr_strftime(status->filename, &rs, sizeof(status->filename), config->szLogRoot, &e);
    }
    else {
        if (config->truncate) {
            apr_snprintf(status->filename, sizeof(status->filename), "%s", config->szLogRoot);
        }
        else {
            apr_snprintf(status->filename, sizeof(status->filename), "%s.%010d", config->szLogRoot,
                    tLogStart);
        }
    }
    apr_pool_create(&status->pfile, status->pool);
    if (config->verbose) {
        fprintf(stderr, "Opening file %s\n", status->filename);
    }
    rv = apr_file_open(&status->nLogFD, status->filename, APR_WRITE | APR_CREATE | APR_APPEND
                       | (config->truncate ? APR_TRUNCATE : 0), APR_OS_DEFAULT, status->pfile);
    if (rv != APR_SUCCESS) {
        char error[120];

        apr_strerror(rv, error, sizeof error);

        /* Uh-oh. Failed to open the new log file. Try to clear
         * the previous log file, note the lost log entries,
         * and keep on truckin'. */
        if (status->nLogFDprev == NULL) {
            fprintf(stderr, "Could not open log file '%s' (%s)\n", status->filename, error);
            exit(2);
        }
        else {
            apr_size_t nWrite;
            status->nLogFD = status->nLogFDprev;
            apr_pool_destroy(status->pfile);
            status->pfile = status->pfile_prev;
            /* Try to keep this error message constant length
             * in case it occurs several times. */
            apr_snprintf(status->errbuf, sizeof status->errbuf,
                         "Resetting log file due to error opening "
                         "new log file, %10d messages lost: %-25.25s\n",
                         status->nMessCount, error);
            nWrite = strlen(status->errbuf);
            apr_file_trunc(status->nLogFD, 0);
            if (apr_file_write(status->nLogFD, status->errbuf, &nWrite) != APR_SUCCESS) {
                fprintf(stderr, "Error writing to the file %s\n", status->filename);
                exit(2);
            }
        }
    }
    else {
        closeFile(config, status->pfile_prev, status->nLogFDprev);
        status->nLogFDprev = NULL;
        status->pfile_prev = NULL;
    }
    status->nMessCount = 0;
    if (config->linkfile) {
        apr_file_remove(config->linkfile, status->pfile);
        if (config->verbose) {
            fprintf(stderr,"Linking %s to %s\n", status->filename, config->linkfile);
        }
        rv = apr_file_link(status->filename, config->linkfile);
        if (rv != APR_SUCCESS) {
            char error[120];
            apr_strerror(rv, error, sizeof error);
            fprintf(stderr, "Error linking file %s to %s (%s)\n",
                    status->filename, config->linkfile, error);
            exit(2);
        }
    }
}

/*
 * Get a size or time param from a string.
 * Parameter 'last' indicates, whether the
 * argument is the last commadnline argument.
