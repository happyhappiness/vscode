        exit(0);
    }
    apr_file_printf(errfile, "password for user %s\n", user);

    /* The temporary file has all the data, just copy it to the new location.
     */
    if (apr_file_copy(dirname, pwfilename, APR_FILE_SOURCE_PERMS, pool) !=
        APR_SUCCESS) {
        apr_file_printf(errfile, "%s: unable to update file %s\n", 
                        argv[0], pwfilename);
        exit(ERR_FILEPERM);
    }
    apr_file_close(ftemp);
