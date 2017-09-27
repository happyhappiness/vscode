    }
    return APR_SUCCESS;
}

static void htdbm_usage(void)
{
    fprintf(stderr,
        "htdbm -- program for manipulating DBM password databases.\n\n"
        "Usage: htdbm   [-cimBdpstvx] [-C cost] [-TDBTYPE] database username\n"
        "                -b[cmBdptsv] [-C cost] [-TDBTYPE] database username password\n"
        "                -n[imBdpst]  [-C cost] username\n"
        "                -nb[mBdpst]  [-C cost] username password\n"
        "                -v[imBdps]   [-C cost] [-TDBTYPE] database username\n"
        "                -vb[mBdps]   [-C cost] [-TDBTYPE] database username password\n"
        "                -x                     [-TDBTYPE] database username\n"
        "                -l                     [-TDBTYPE] database\n"
        "Options:\n"
        "   -c   Create a new database.\n"
        "   -n   Don't update database; display results on stdout.\n"
        "   -b   Use the password from the command line rather than prompting for it.\n"
        "   -i   Read password from stdin without verification (for script usage).\n"
        "   -m   Force MD5 encryption of the password (default).\n"
        "   -B   Force BCRYPT encryption of the password (very secure).\n"
        "   -C   Set the computing time used for the bcrypt algorithm\n"
        "        (higher is more secure but slower, default: %d, valid: 4 to 31).\n"
        "   -d   Force CRYPT encryption of the password (8 chars max, insecure).\n"
        "   -s   Force SHA encryption of the password (insecure).\n"
        "   -p   Do not encrypt the password (plaintext, insecure).\n"
        "   -T   DBM Type (SDBM|GDBM|DB|default).\n"
        "   -l   Display usernames from database on stdout.\n"
        "   -v   Verify the username/password.\n"
        "   -x   Remove the username record from database.\n"
        "   -t   The last param is username comment.\n"
        "The SHA algorithm does not use a salt and is less secure than the "
        "MD5 algorithm.\n",
        BCRYPT_DEFAULT_COST);
    exit(ERR_SYNTAX);
}

int main(int argc, const char * const argv[])
{
    apr_pool_t *pool;
    apr_status_t rv;
    char errbuf[MAX_STRING_LEN];
    int  need_file = 1;
    int  need_user = 1;
    int  need_pwd  = 1;
    int  need_cmnt = 0;
    int  changed = 0;
    int  cmd = HTDBM_MAKE;
    int  i, ret, args_left = 2;
    apr_getopt_t *state;
    char opt;
    const char *opt_arg;

    apr_app_initialize(&argc, &argv, NULL);
    atexit(terminate);

    if ((rv = htdbm_init(&pool, &h)) != APR_SUCCESS) {
        fprintf(stderr, "Unable to initialize htdbm terminating!\n");
        apr_strerror(rv, errbuf, sizeof(errbuf));
        exit(1);
    }

    rv = apr_getopt_init(&state, pool, argc, argv);
    if (rv != APR_SUCCESS)
        exit(ERR_SYNTAX);

    while ((rv = apr_getopt(state, "cnmspdBbDivxlC:T:", &opt, &opt_arg)) == APR_SUCCESS) {
        switch (opt) {
        case 'c':
            h->create = 1;
            break;
        case 'n':
            need_file = 0;
            cmd = HTDBM_NOFILE;
                args_left--;
            break;
        case 'l':
            need_pwd = 0;
            need_user = 0;
            cmd = HTDBM_LIST;
            h->rdonly = 1;
            args_left--;
            break;
        case 't':
            need_cmnt = 1;
            args_left++;
            break;
        case 'T':
            h->type = apr_pstrdup(h->ctx.pool, opt_arg);
            break;
        case 'v':
            h->rdonly = 1;
            cmd = HTDBM_VERIFY;
            break;
        case 'x':
            need_pwd = 0;
            cmd = HTDBM_DELETE;
            break;
        default:
            ret = parse_common_options(&h->ctx, opt, opt_arg);
            if (ret) {
                fprintf(stderr, "Error: %s\n", h->ctx.errstr);
                exit(ret);
            }
        }
    }
    if (h->ctx.passwd_src == PW_ARG) {
            need_pwd = 0;
            args_left++;
    }
    /*
     * Make sure we still have exactly the right number of arguments left
     * (the filename, the username, and possibly the password if -b was
     * specified).
     */
    i = state->ind;
    if (rv != APR_EOF || argc - i != args_left)
        htdbm_usage();

    if (need_file) {
        h->filename = apr_pstrdup(h->ctx.pool, argv[i++]);
        if ((rv = htdbm_open(h)) != APR_SUCCESS) {
            fprintf(stderr, "Error opening database %s\n", h->filename);
            apr_strerror(rv, errbuf, sizeof(errbuf));
            fprintf(stderr,"%s\n",errbuf);
            exit(ERR_FILEPERM);
        }
    }
    if (need_user) {
        h->username = apr_pstrdup(pool, argv[i++]);
        if (htdbm_valid_username(h) != APR_SUCCESS)
            exit(ERR_BADUSER);
    }
    if (h->ctx.passwd_src == PW_ARG)
        h->ctx.passwd = apr_pstrdup(pool, argv[i++]);

    if (need_pwd) {
        ret = get_password(&h->ctx);
        if (ret) {
            fprintf(stderr, "Error: %s\n", h->ctx.errstr);
            exit(ret);
        }
    }
    if (need_cmnt)
        h->comment = apr_pstrdup(pool, argv[i++]);

    switch (cmd) {
        case HTDBM_VERIFY:
            if ((rv = htdbm_verify(h)) != APR_SUCCESS) {
                if (APR_STATUS_IS_ENOENT(rv)) {
                    fprintf(stderr, "The user '%s' could not be found in database\n", h->username);
