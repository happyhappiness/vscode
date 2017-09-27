
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
