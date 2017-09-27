(mask & APHTP_VERIFY) {
        apr_file_printf(errfile, "Password for user %s correct." NL, user);
        exit(0);
    }

    apr_file_printf(errfile, "password for user %s" NL, user);