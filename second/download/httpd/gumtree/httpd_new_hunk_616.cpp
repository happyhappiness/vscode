	arg = argv[i];
	if (*arg != '-') {
	    break;
	}
	while (*++arg != '\0') {
	    if (*arg == 'c') {
                *mask |= APHTP_NEWFILE;
	    }
	    else if (*arg == 'n') {
                *mask |= APHTP_NOFILE;
		args_left--;
	    }
	    else if (*arg == 'm') {
                *alg = ALG_APMD5;
	    }
	    else if (*arg == 's') {
                *alg = ALG_APSHA;
	    }
	    else if (*arg == 'p') {
                *alg = ALG_PLAIN;
	    }
	    else if (*arg == 'd') {
                *alg = ALG_CRYPT;
	    }
	    else if (*arg == 'b') {
                *mask |= APHTP_NONINTERACTIVE;
		args_left++;
	    }
	    else {
                usage();
	    }
	}
    }

    if (*mask & (APHTP_NEWFILE | APHTP_NOFILE)) {
        apr_file_printf(errfile, "%s: -c and -n options conflict\n", argv[0]);
        exit(ERR_SYNTAX);
    }
    /*
     * Make sure we still have exactly the right number of arguments left
     * (the filename, the username, and possibly the password if -b was
     * specified).
     */
    if ((argc - i) != args_left) {
        usage();
    }

    if (*mask & APHTP_NOFILE) {
	i--;
    }
    else {
        if (strlen(argv[i]) > (APR_PATH_MAX - 1)) {
            apr_file_printf(errfile, "%s: filename too long\n", argv[0]);
            exit(ERR_OVERFLOW);
        }
        *pwfilename = apr_pstrdup(pool, argv[i]);
        if (strlen(argv[i + 1]) > (MAX_STRING_LEN - 1)) {
            apr_file_printf(errfile, "%s: username too long (> %d)\n",
                argv[0], MAX_STRING_LEN - 1);
            exit(ERR_OVERFLOW);
	}
    }
    *user = apr_pstrdup(pool, argv[i + 1]);
    if ((arg = strchr(*user, ':')) != NULL) {
        apr_file_printf(errfile, "%s: username contains illegal character '%c'\n",
		argv[0], *arg);
        exit(ERR_BADUSER);
    }
    if (*mask & APHTP_NONINTERACTIVE) {
        if (strlen(argv[i + 2]) > (MAX_STRING_LEN - 1)) {
            apr_file_printf(errfile, "%s: password too long (> %d)\n",
                argv[0], MAX_STRING_LEN);
            exit(ERR_OVERFLOW);
	}
        *password = apr_pstrdup(pool, argv[i + 2]);
    }
}

/*
 * Let's do it.  We end up doing a lot of file opening and closing,
 * but what do we care?  This application isn't run constantly.
 */
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
    char *str = NULL;
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
