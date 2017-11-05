apr_file_printf(errfile, "%s: The file %s does not appear "
                                         "to be a valid htpasswd file." NL,
                                argv[0], pwfilename);