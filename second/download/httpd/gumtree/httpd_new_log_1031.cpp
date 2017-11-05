apr_file_printf(errfile, "%s: username too long (> %d)" NL,
                argv[0], MAX_STRING_LEN - 1);