        fprintf(stderr, "Unable to open stdin\n");
        exit(1);
    }

    for (;;) {
        nRead = sizeof(buf);
        /*
         * Bypass reading stdin if we are forcing the logfile
         * to be opened as soon as we start. Since we won't be
         * writing anything, we just want to open the file.
         * First time through is the only time we do this
         * since we reset bypass_io after the 1st loop
         */
        if (!bypass_io) {
            if (apr_file_read(f_stdin, buf, &nRead) != APR_SUCCESS) {
                exit(3);
            }
        }
        if (tRotation) {
            now = get_now(use_localtime, utc_offset);
            if (nLogFD != NULL && now >= tLogEnd) {
                nLogFDprev = nLogFD;
                nLogFD = NULL;
            }
        }
        else if (sRotation) {
