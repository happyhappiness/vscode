int main(int argc, const char * const argv[])
{
    apr_file_t *fpw = NULL;
    char record[MAX_STRING_LEN];
    char line[MAX_STRING_LEN];
    char *password = NULL;
    char *pwfilename = NULL;
    char *user = NULL;
    char tn[] = "htpasswd.tmp.XXXXXX";
    char scratch[MAX_STRING_LEN];
    int found = 0;
    int i;
    int alg = ALG_CRYPT;
    int mask = 0;
    apr_pool_t *pool;
#if APR_CHARSET_EBCDIC
    apr_status_t rv;
    apr_xlate_t *to_ascii;
#endif

    apr_app_initialize(&argc, &argv, NULL);
    atexit(apr_terminate);
#ifdef NETWARE
    atexit(nwTerminate);
#endif
    apr_pool_create(&pool, NULL);
    apr_file_open_stderr(&errfile, pool);

#if APR_CHARSET_EBCDIC
    rv = apr_xlate_open(&to_ascii, "ISO8859-1", APR_DEFAULT_CHARSET, pool);
    if (rv) {
        apr_file_printf(errfile, "apr_xlate_open(to ASCII)->%d\n", rv);
        exit(1);
    }
    rv = apr_SHA1InitEBCDIC(to_ascii);
    if (rv) {
        apr_file_printf(errfile, "apr_SHA1InitEBCDIC()->%d\n", rv);
        exit(1);
    }
    rv = apr_MD5InitEBCDIC(to_ascii);
    if (rv) {
        apr_file_printf(errfile, "apr_MD5InitEBCDIC()->%d\n", rv);
        exit(1);
    }
#endif /*APR_CHARSET_EBCDIC*/

    check_args(pool, argc, argv, &alg, &mask, &user, &pwfilename, &password);


#if defined(WIN32) || defined(NETWARE)
    if (alg == ALG_CRYPT) {
        alg = ALG_APMD5;
        apr_file_printf(errfile, "Automatically using MD5 format.\n");
    }
#endif

#if (!(defined(WIN32) || defined(TPF) || defined(NETWARE)))
    if (alg == ALG_PLAIN) {
        apr_file_printf(errfile,"Warning: storing passwords as plain text might "
                "just not work on this platform.\n");
    }
#endif
    if (! mask & APHTP_NOFILE) {
        /*
         * Only do the file checks if we're supposed to frob it.
         *
         * Verify that the file exists if -c was omitted.  We give a special
         * message if it doesn't.
         */
        if ((! mask & APHTP_NEWFILE) && (! exists(pwfilename, pool))) {
            apr_file_printf(errfile,
                    "%s: cannot modify file %s; use '-c' to create it\n",
                    argv[0], pwfilename);
            perror("apr_file_open");
            exit(ERR_FILEPERM);
        }
        /*
         * Verify that we can read the existing file in the case of an update
         * to it (rather than creation of a new one).
         */
        if ((! mask & APHTP_NEWFILE) && (! readable(pool, pwfilename))) {
            apr_file_printf(errfile, "%s: cannot open file %s for read access\n",
                    argv[0], pwfilename);
            perror("apr_file_open");
            exit(ERR_FILEPERM);
        }
        /*
         * Now check to see if we can preserve an existing file in case
         * of password verification errors on a -c operation.
         */
        if ((mask & APHTP_NEWFILE) && exists(pwfilename, pool) && 
            (! readable(pool, pwfilename))) {
            apr_file_printf(errfile, "%s: cannot open file %s for read access\n"
                    "%s: existing auth data would be lost on "
                    "password mismatch",
                    argv[0], pwfilename, argv[0]);
            perror("apr_file_open");
            exit(ERR_FILEPERM);
        }
        /*
         * Now verify that the file is writable!
         */
        if (! writable(pool, pwfilename)) {
            apr_file_printf(errfile, "%s: cannot open file %s for write access\n",
                    argv[0], pwfilename);
            perror("apr_file_open");
            exit(ERR_FILEPERM);
        }
    }

    /*
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
    if (apr_file_mktemp(&ftemp, tn, 0, pool) != APR_SUCCESS) {
        apr_file_printf(errfile, "%s: unable to create temporary file '%s'\n", 
                        argv[0], tn);
        exit(ERR_FILEPERM);
    }

    /*
     * If we're not creating a new file, copy records from the existing
     * one to the temporary file until we find the specified user.
     */
    if (apr_file_open(&fpw, pwfilename, APR_READ, APR_OS_DEFAULT, 
                      pool) == APR_SUCCESS) {
        while (! (apr_file_gets(line, sizeof(line), fpw))) {
            char *colon;

            if ((line[0] == '#') || (line[0] == '\0')) {
                putline(ftemp, line);
                continue;
            }
            strcpy(scratch, line);
            /*
             * See if this is our user.
             */
            colon = strchr(scratch, ':');
            if (colon != NULL) {
                *colon = '\0';
            }
            if (strcmp(user, scratch) != 0) {
                putline(ftemp, line);
                continue;
            }
            else {
                /* We found the user we were looking for, add him to the file.
                 */
                apr_file_printf(errfile, "Updating ");
                putline(ftemp, record);
                found++;
            }
        }
        apr_file_close(fpw);
    }
    if (!found) {
        apr_file_printf(errfile, "Adding ");
        putline(ftemp, record);
    }
    apr_file_printf(errfile, "password for user %s\n", user);

    /* The temporary file has all the data, just copy it to the new location.
     */
    apr_file_copy(tn, pwfilename, APR_FILE_SOURCE_PERMS, pool);
    apr_file_close(ftemp);
    return 0;
}