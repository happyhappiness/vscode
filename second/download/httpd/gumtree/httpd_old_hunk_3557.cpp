    else if (need_cmnt)
        h->comment = apr_pstrdup(pool, argv[i+2]);

    switch (cmd) {
        case HTDBM_VERIFY:
            if ((rv = htdbm_verify(h)) != APR_SUCCESS) {
                if(rv == APR_ENOENT) {
                    fprintf(stderr, "The user '%s' could not be found in database\n", h->username);
                    exit(ERR_BADUSER);
                }
                else {
                    fprintf(stderr, "Password mismatch for user '%s'\n", h->username);
                    exit(ERR_PWMISMATCH);
