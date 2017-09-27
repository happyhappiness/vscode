                        argv[0], pwfilename);
                exit(ERR_FILEPERM);
            }
            /*
             * As it doesn't exist yet, verify that we can create it.
             */
            if (!accessible(pool, pwfilename, APR_FOPEN_WRITE|APR_FOPEN_CREATE)) {
                apr_file_printf(errfile, "%s: cannot create file %s" NL,
                                argv[0], pwfilename);
                exit(ERR_FILEPERM);
            }
        }
    }
