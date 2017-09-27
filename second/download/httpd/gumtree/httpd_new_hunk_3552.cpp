{
    apr_status_t rv;
    apr_dir_t *dirp;
    apr_finfo_t dirent;

    rv = apr_dir_open(&dirp, dir, pool);
    if (APR_STATUS_IS_ENOENT(rv)) {
        return rv;
    }
    if (rv != APR_SUCCESS) {
        char errmsg[120];
        apr_file_printf(errfile, "Could not open directory %s: %s" APR_EOL_STR,
                dir, apr_strerror(rv, errmsg, sizeof errmsg));
