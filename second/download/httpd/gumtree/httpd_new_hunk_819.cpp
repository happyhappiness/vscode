
    /*
     * We can access the files the right way, and we have a record
     * to add or update.  Let's do it..
     */
    if (apr_file_mktemp(&ftemp, tn, 0, pool) != APR_SUCCESS) {
        apr_file_printf(errfile, "%s: unable to create temporary file %s\n", 
                        argv[0], tn);
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

            if ((line[0] == '#') || (line[0] == '\0')) {
                putline(ftemp, line);
                continue;
            }
