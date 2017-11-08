int main(int argc, const char * const argv[])
{
    apr_pool_t *pool;
    apr_status_t rv;
    apr_size_t l;
    char pwi[MAX_STRING_LEN];
    char pwc[MAX_STRING_LEN];
    char errbuf[MAX_STRING_LEN];
    const char *arg;
    int  need_file = 1;
    int  need_user = 1;
    int  need_pwd  = 1;
    int  need_cmnt = 0;
    int  pwd_supplied = 0;
    int  changed = 0;
    int  cmd = HTDBM_MAKE;
    int  i;
    int args_left = 2;

    apr_app_initialize(&argc, &argv, NULL);
    atexit(terminate);

    if ((rv = htdbm_init(&pool, &h)) != APR_SUCCESS) {
        fprintf(stderr, "Unable to initialize htdbm terminating!\n");
        apr_strerror(rv, errbuf, sizeof(errbuf));
        exit(1);
    }
    /*
     * Preliminary check to make sure they provided at least
     * three arguments, we'll do better argument checking as
     * we parse the command line.
     */
    if (argc < 3)
       htdbm_usage();
    /*
     * Go through the argument list and pick out any options.  They
     * have to precede any other arguments.
     */
    for (i = 1; i < argc; i++) {
        arg = argv[i];
        if (*arg != '-')
            break;

        while (*++arg != '\0') {
            switch (*arg) {
            case 'b':
                pwd_supplied = 1;
                need_pwd = 0;
                args_left++;
                break;
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
                h->type = apr_pstrdup(h->pool, ++arg);
                while (*arg != '\0')
                    ++arg;
                --arg; /* so incrementing this in the loop with find a null */
                break;
            case 'v':
                h->rdonly = 1;
                cmd = HTDBM_VERIFY;
                break;
            case 'x':
                need_pwd = 0;
                cmd = HTDBM_DELETE;
                break;
            case 'm':
                h->alg = ALG_APMD5;
                break;
            case 'p':
                h->alg = ALG_PLAIN;
                break;
            case 's':
                h->alg = ALG_APSHA;
                break;
#if APR_HAVE_CRYPT_H
            case 'd':
                h->alg = ALG_CRYPT;
                break;
#endif
            default:
                htdbm_usage();
                break;
            }
        }
    }
    /*
     * Make sure we still have exactly the right number of arguments left
     * (the filename, the username, and possibly the password if -b was
     * specified).
     */
    if ((argc - i) != args_left)
        htdbm_usage();

    if (!need_file)
        i--;
    else {
        h->filename = apr_pstrdup(h->pool, argv[i]);
            if ((rv = htdbm_open(h)) != APR_SUCCESS) {
            fprintf(stderr, "Error opening database %s\n", argv[i]);
            apr_strerror(rv, errbuf, sizeof(errbuf));
            fprintf(stderr,"%s\n",errbuf);
            exit(ERR_FILEPERM);
        }
    }
    if (need_user) {
        h->username = apr_pstrdup(pool, argv[i+1]);
        if (htdbm_valid_username(h) != APR_SUCCESS)
            exit(ERR_BADUSER);
    }
    if (pwd_supplied)
        h->userpass = apr_pstrdup(pool, argv[i+2]);

    if (need_pwd) {
        l = sizeof(pwc);
        if (apr_password_get("Enter password        : ", pwi, &l) != APR_SUCCESS) {
            fprintf(stderr, "Password too long\n");
            exit(ERR_OVERFLOW);
        }
        l = sizeof(pwc);
        if (apr_password_get("Re-type password      : ", pwc, &l) != APR_SUCCESS) {
            fprintf(stderr, "Password too long\n");
            exit(ERR_OVERFLOW);
        }
        if (strcmp(pwi, pwc) != 0) {
         