    apr_terminate();
#ifdef NETWARE
    pressanykey();
#endif
}

static void check_args(int argc, const char *const argv[],
                       struct passwd_ctx *ctx, int *mask, char **user,
                       char **pwfilename)
{
    const char *arg;
    int args_left = 2;
    int i, ret;
    apr_getopt_t *state;
    apr_status_t rv;
    char opt;
    const char *opt_arg;
    apr_pool_t *pool = ctx->pool;

    rv = apr_getopt_init(&state, pool, argc, argv);
    if (rv != APR_SUCCESS)
        exit(ERR_SYNTAX);

    while ((rv = apr_getopt(state, "cnmspdBbDiC:", &opt, &opt_arg)) == APR_SUCCESS) {
        switch (opt) {
        case 'c':
            *mask |= APHTP_NEWFILE;
            break;
        case 'n':
            args_left--;
            *mask |= APHTP_NOFILE;
            break;
        case 'D':
            *mask |= APHTP_DELUSER;
            break;
        default:
            ret = parse_common_options(ctx, opt, opt_arg);
            if (ret) {
                apr_file_printf(errfile, "%s: %s" NL, argv[0], ctx->errstr);
                exit(ret);
            }
        }
    }
    if (ctx->passwd_src == PW_ARG)
        args_left++;
    if (rv != APR_EOF)
        usage();

    if ((*mask & APHTP_NEWFILE) && (*mask & APHTP_NOFILE)) {
        apr_file_printf(errfile, "%s: -c and -n options conflict" NL, argv[0]);
        exit(ERR_SYNTAX);
    }
    if ((*mask & APHTP_NEWFILE) && (*mask & APHTP_DELUSER)) {
