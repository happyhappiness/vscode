            doRotate(&config, &status);
        }

        nWrite = nRead;
        rv = apr_file_write_full(status.current.fd, buf, nWrite, &nWrite);
        if (nWrite != nRead) {
            apr_off_t cur_offset;

            cur_offset = 0;
            if (apr_file_seek(status.current.fd, APR_CUR, &cur_offset) != APR_SUCCESS) {
                cur_offset = -1;
            }
            status.nMessCount++;
            apr_snprintf(status.errbuf, sizeof status.errbuf,
                         "Error %d writing to log file at offset %" APR_OFF_T_FMT ". "
                         "%10d messages lost (%pm)\n",
                         rv, cur_offset, status.nMessCount, &rv);

            truncate_and_write_error(&status);
        }
        else {
            status.nMessCount++;
        }
        if (config.echo) {
            if (apr_file_write_full(f_stdout, buf, nRead, &nWrite)) {
