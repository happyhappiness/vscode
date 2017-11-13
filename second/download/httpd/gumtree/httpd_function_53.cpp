static void check_args(apr_pool_t *pool, int argc, const char *const argv[], 
                       int *alg, int *mask, char **user, char **pwfilename, 
                       char **password)
{
    const char *arg;
    int args_left = 2;
    int i;

    /*
     * Preliminary check to make sure they provided at least
     * three arguments, we'll do better argument checking as 
     * we parse the command line.
     */
    if (argc < 3) {
        usage();
    }

    /*
     * Go through the argument list and pick out any options.  They
     * have to precede any other arguments.
     */
    for (i = 1; i < argc; i++) {
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

    if ((*mask & APHTP_NEWFILE) && (*mask & APHTP_NOFILE)) {
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