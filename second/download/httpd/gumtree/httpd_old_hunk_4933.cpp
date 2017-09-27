    apr_terminate();
#ifdef NETWARE
    pressanykey();
#endif
}

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
            else if (*arg == 'D') {
                *mask |= APHTP_DELUSER;
            }
            else {
                usage();
            }
        }
    }

    if ((*mask & APHTP_NEWFILE) && (*mask & APHTP_NOFILE)) {
        apr_file_printf(errfile, "%s: -c and -n options conflict" NL, argv[0]);
        exit(ERR_SYNTAX);
    }
    if ((*mask & APHTP_NEWFILE) && (*mask & APHTP_DELUSER)) {
