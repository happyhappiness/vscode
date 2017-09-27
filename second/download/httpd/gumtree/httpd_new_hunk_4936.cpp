     * try to create the record for the username in question.  If that
     * fails, there's no need to waste any time on file manipulations.
     * Any error message text is returned in the record buffer, since
     * the mkrecord() routine doesn't have access to argv[].
     */
    if (!(mask & APHTP_DELUSER)) {
        i = mkrecord(&ctx, user);
        if (i != 0) {
            apr_file_printf(errfile, "%s: %s" NL, argv[0], errstr);
            exit(i);
        }
        if (mask & APHTP_NOFILE) {
            printf("%s" NL, ctx.out);
            exit(0);
        }
    }

    /*
     * We can access the files the right way, and we have a record
