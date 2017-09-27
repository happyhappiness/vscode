     * the mkrecord() routine doesn't have access to argv[].
     */
    if (!(mask & APHTP_DELUSER)) {
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
    }

    /*
     * We can access the files the right way, and we have a record
     * to add or update.  Let's do it..
     */
    if (apr_temp_dir_get((const char**)&dirname, pool) != APR_SUCCESS) {
        apr_file_printf(errfile, "%s: could not determine temp dir\n",
                        argv[0]);
        exit(ERR_FILEPERM);
    }
    dirname = apr_psprintf(pool, "%s/%s", dirname, tn);

    if (apr_file_mktemp(&ftemp, dirname, 0, pool) != APR_SUCCESS) {
        apr_file_printf(errfile, "%s: unable to create temporary file %s\n", 
                        argv[0], dirname);
        exit(ERR_FILEPERM);
    }

    /*
     * If we're not creating a new file, copy records from the existing
     * one to the temporary file until we find the specified user.
     */
    if (existing_file && !(mask & APHTP_NEWFILE)) {
        if (apr_file_open(&fpw, pwfilename, APR_READ | APR_BUFFERED,
                          APR_OS_DEFAULT, pool) != APR_SUCCESS) {
            apr_file_printf(errfile, "%s: unable to read file %s\n", 
                            argv[0], pwfilename);
            exit(ERR_FILEPERM);
        }
        while (apr_file_gets(line, sizeof(line), fpw) == APR_SUCCESS) {
            char *colon;

