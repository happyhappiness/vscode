     * All the file access checks (if any) have been made.  Time to go to work;
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
     * to add or update.  Let's do it..
     */
    if (apr_temp_dir_get((const char**)&dirname, pool) != APR_SUCCESS) {
        apr_file_printf(errfile, "%s: could not determine temp dir" NL,
                        argv[0]);
        exit(ERR_FILEPERM);
    }
    dirname = apr_psprintf(pool, "%s/%s", dirname, tn);

    if (apr_file_mktemp(&ftemp, dirname, 0, pool) != APR_SUCCESS) {
        apr_file_printf(errfile, "%s: unable to create temporary file %s" NL,
                        argv[0], dirname);
        exit(ERR_FILEPERM);
    }

    /*
     * If we're not creating a new file, copy records from the existing
     * one to the temporary file until we find the specified user.
     */
