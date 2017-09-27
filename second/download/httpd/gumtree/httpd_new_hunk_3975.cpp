     * routines, that file may or may not actually be created. We'd
     * like to store those files in the operating system's designated
     * temporary directory, which APR can point us to.
     */
    rs = apr_temp_dir_get(&tempdir, pconf);
    if (APR_SUCCESS != rs) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rs, s, APLOGNO(02992)
                     "Failed to find temporary directory");
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    /* Create the shared memory segment */

