        fprintf(stderr, "Unable to open stdin\n");
        exit(1);
    }

    for (;;) {
        nRead = sizeof(buf);
        if (apr_file_read(f_stdin, buf, &nRead) != APR_SUCCESS)
            exit(3);
        if (tRotation) {
            now = (int)(apr_time_now() / APR_USEC_PER_SEC) + utc_offset;
            if (nLogFD != NULL && now >= tLogEnd) {
                nLogFDprev = nLogFD;
                nLogFD = NULL;
            }
        }
