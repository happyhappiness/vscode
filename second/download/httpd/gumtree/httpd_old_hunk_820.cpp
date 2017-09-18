        putline(ftemp, record);
    }
    apr_file_printf(errfile, "password for user %s\n", user);

    /* The temporary file has all the data, just copy it to the new location.
     */
    apr_file_copy(tn, pwfilename, APR_FILE_SOURCE_PERMS, pool);
    apr_file_close(ftemp);
    return 0;
}
