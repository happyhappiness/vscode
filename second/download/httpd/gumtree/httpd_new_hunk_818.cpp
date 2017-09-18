        apr_file_printf(errfile, "Automatically using MD5 format.\n");
    }
#endif

#if (!(defined(WIN32) || defined(TPF) || defined(NETWARE)))
    if (alg == ALG_PLAIN) {
        apr_file_printf(errfile,"Warning: storing passwords as plain text "
                        "might just not work on this platform.\n");
    }
#endif

    /*
     * Only do the file checks if we're supposed to frob it.
     */
    if (!(mask & APHTP_NOFILE)) {
        existing_file = exists(pwfilename, pool);
        if (existing_file) {
            /*
             * Check that this existing file is readable and writable.
             */
            if (!accessible(pool, pwfilename, APR_READ | APR_APPEND)) {
                apr_file_printf(errfile, "%s: cannot open file %s for "
                                "read/write access\n", argv[0], pwfilename);
                exit(ERR_FILEPERM);
            }
        }
        else {
            /*
             * Error out if -c was omitted for this non-existant file.
             */
            if (!(mask & APHTP_NEWFILE)) {
                apr_file_printf(errfile,
                        "%s: cannot modify file %s; use '-c' to create it\n",
                        argv[0], pwfilename);
                exit(ERR_FILEPERM);
            }
            /*
             * As it doesn't exist yet, verify that we can create it.
             */
            if (!accessible(pool, pwfilename, APR_CREATE | APR_WRITE)) {
                apr_file_printf(errfile, "%s: cannot create file %s\n",
                                argv[0], pwfilename);
                exit(ERR_FILEPERM);
            }
        }
    }

    /*
     * All the file access checks (if any) have been made.  Time to go to work;
     * try to create the record for the username in question.  If that
