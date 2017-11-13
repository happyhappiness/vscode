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
                    exit(ERR_BADUSER);
                }
                else {
                    fprintf(stderr, "Password mismatch for user '%s'\n", h->username);
                    exit(ERR_PWMISMATCH);
                }
            }
            else
                fprintf(stderr, "Password validated for user '%s'\n", h->username);
            break;
        case HTDBM_DELETE:
            if (htdbm_del(h) != APR_SUCCESS) {
                fprintf(stderr, "Cannot find user '%s' in database\n", h->username);
                exit(ERR_BADUSER);
            }
            h->username = NULL;
            changed = 1;
            break;
        case HTDBM_LIST:
            htdbm_list(h);
            break;
        default:
            ret = htdbm_make(h);
            if (ret)
                exit(ret);
            break;
    }
    if (need_file && !h->rdonly) {
        if ((rv = htdbm_save(h, &changed)) != APR_SUCCESS) {
            apr_strerror(rv, errbuf, sizeof(errbuf));
            exit(ERR_FILEPERM);
        }
        fprintf(stdout, "Database %s %s.\n", h->filename,
                h->create ? "created" : (changed ? "modified" : "updated"));
    }
    if (cmd == HTDBM_NOFILE) {
        if (!need_cmnt) {
            fprintf(stderr, "%s:%s\n", h->username, h->ctx.passwd);
        }
        else {
            fprintf(stderr, "%s:%s:%s\n", h->username, h->ctx.passwd,
                    h->comment);
        }
    }
    htdbm_terminate(h);

    return 0; /* Suppress compiler warning. */
}