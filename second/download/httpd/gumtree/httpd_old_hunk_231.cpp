     * All the file access checks (if any) have been made.  Time to go to work;
     * try to create the record for the username in question.  If that
     * fails, there's no need to waste any time on file manipulations.
     * Any error message text is returned in the record buffer, since
     * the mkrecord() routine doesn't have access to argv[].
     */
    i = mkrecord(user, record, sizeof(record) - 1,
                 password, alg);
    if (i != 0) {
        apr_file_printf(errfile, "%s: %s\n", argv[0], record);
        exit(i);
    }
    if (mask & APHTP_NOFILE) {
        printf("%s\n", record);
        exit(0);
    }

    /*
     * We can access the files the right way, and we have a record
     * to add or update.  Let's do it..
     */
