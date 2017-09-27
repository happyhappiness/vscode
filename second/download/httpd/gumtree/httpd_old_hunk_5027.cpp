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
