apr_file_printf(errfile, "%s: username too long (> %d)\n",
                argv[0], MAX_STRING_LEN - 1);