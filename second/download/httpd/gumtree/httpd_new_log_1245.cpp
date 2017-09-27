apr_file_printf(errfile,
                        "%s: cannot modify file %s; use '-c' to create it" NL,
                        argv[0], pwfilename);