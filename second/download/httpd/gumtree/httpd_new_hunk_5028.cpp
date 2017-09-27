    }
    if (ctx->passwd_src == PW_ARG)
        args_left++;
    if (rv != APR_EOF)
        usage();

    if ((*mask) & (*mask - 1)) {
        /* not a power of two, i.e. more than one flag specified */
        apr_file_printf(errfile, "%s: only one of -c -n -v -D may be specified" NL,
            argv[0]);
        exit(ERR_SYNTAX);
    }
    if ((*mask & APHTP_VERIFY) && ctx->passwd_src == PW_PROMPT)
        ctx->passwd_src = PW_PROMPT_VERIFY;

    /*
     * Make sure we still have exactly the right number of arguments left
     * (the filename, the username, and possibly the password if -b was
     * specified).
     */
    i = state->ind;
