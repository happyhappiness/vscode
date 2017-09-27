            doRotate(&config, &status);
        }

        nWrite = nRead;
        rv = apr_file_write_full(status.current.fd, buf, nWrite, &nWrite);
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
            if (apr_file_write_full(status.current.fd, status.errbuf, nWrite, NULL) != APR_SUCCESS) {
                fprintf(stderr, "Error writing to the file %s\n", status.current.name);
                exit(2);
            }
        }
        else {
            status.nMessCount++;
        }
        if (config.echo) {
            if (apr_file_write_full(f_stdout, buf, nRead, &nWrite)) {
