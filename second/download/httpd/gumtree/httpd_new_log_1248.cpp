apr_file_printf(errfile, "%s: password too long (> %d)" NL,
                argv[0], MAX_STRING_LEN);