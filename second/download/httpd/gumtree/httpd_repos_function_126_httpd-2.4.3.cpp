int main(int argc, const char * const argv[])
{
    apr_file_t *fpw = NULL;
    char record[MAX_STRING_LEN];
    char line[MAX_STRING_LEN];
    char *password = NULL;
    char *pwfilename = NULL;
    char *user = NULL;
    char tn[] = "htpasswd.tmp.XXXXXX";
    char *dirname;
    char *scratch, cp[MAX_STRING_LEN];
    int found = 0;
    int i;
    int alg = ALG_APMD5;
    int mask = 0;
    apr_pool_t *pool;
    int existing_file = 0;
#if APR_CHARSET_EBCDIC
    apr_status_t rv;
    apr_xlate_t *to_ascii;
#endif

    apr_app_initialize(&argc, &argv, NULL);
    atexit(terminate);
    apr_pool_create(&pool, NULL);
    apr_file_open_stderr(&errfile, pool);

#if APR_CHARSET_EBCDIC
    rv = apr_xlate_open(&to_ascii, "ISO-8859-1", APR_DEFAULT_CHARSET, pool);
    if (rv) {
        apr_file_printf(errfile, "apr_xlate_open(to ASCII)->%d" NL, rv);
        exit(1);
    }
    rv = apr_SHA1InitEBCDIC(to_ascii);
    if (rv) {
        apr_file_printf(errfile, "apr_SHA1InitEBCDIC()->%d" NL, rv);
        exit(1);
    }
    rv = apr_MD5InitEBCDIC(to_ascii);
    if (rv) {
        apr_file_printf(errfile, "apr_MD5InitEBCDIC()->%d" NL, rv);
        exit(1);
    }
#endif /*APR_CHARSET_EBCDIC*/

    check_args(pool, argc, argv, &alg, &mask, &user, &pwfilename, &password);


#if !CRYPT_ALGO_SUPPORTED
    if (alg == ALG_CRYPT) {
        alg = ALG_APMD5;
        apr_file_printf(errfile, "Automatically using MD5 format." NL);
    }
#endif

#if CRYPT_ALGO_SUPPORTED
    if (alg == ALG_PLAIN) {
        apr_file_printf(errfile,"Warning: storing passwords as plain text "
                        "might just not work on this platform." NL);
    }
#endif

    /*
     * Only do the file checks if we're supposed to frob it.
     */
    if (!(mask & APHTP_NOFILE)) {
        existing_file = exists(pwfilename, pool);
        if (existing_file) {
            /*
             * Check that this existing file is readable and writable.
             */
            if (!accessible(pool, pwfilename, APR_FOPEN_READ|APR_FOPEN_WRITE)) {
                apr_file_printf(errfile, "%s: cannot open file %s for "
                                "read/write access" NL, argv[0], pwfilename);
                exit(ERR_FILEPERM);
            }
        }
        else {
            /*
             * Error out if -c was omitted for this non-existant file.
             */
            if (!(mask & APHTP_NEWFILE)) {
                apr_file_printf(errfile,
                        "%s: cannot modify file %s; use '-c' to create it" NL,
                        argv[0], pwfilename);
                exit(ERR_FILEPERM);
            }
            /*
             * As it doesn't exist yet, verify that we can create it.
             */
            if (!accessible(pool, pwfilename, APR_FOPEN_WRITE|APR_FOPEN_CREATE)) {
                apr_file_printf(errfile, "%s: cannot create file %s" NL,
                                argv[0], pwfilename);
                exit(ERR_FILEPERM);
            }
        }
    }

    /*
     * All the file access checks (if any) have been made.  Time to go to work;
     * try to create the record for the username in question.  If that
     * fails, there's no need to waste any time on file manipulations.
     * Any error message text is returned in the record buffer, since
     * the mkrecord() routine doesn't have access to argv[].
     */
    if (!(mask & APHTP_DELUSER)) {
        i = mkrecord(user, record, sizeof(record) - 1,
                     password, alg);
        if (i != 0) {
            apr_file_printf(errfile, "%s: %s" NL, argv[0], record);
            exit(i);
        }
        if (mask & APHTP_NOFILE) {
            printf("%s" NL, record);
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
    dirname = apr_psprintf(pool, "%s/%s", dirname, t