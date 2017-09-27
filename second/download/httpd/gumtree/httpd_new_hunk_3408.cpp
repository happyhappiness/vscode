     */
    apr_procattr_create(&attr, ptemp);
    apr_procattr_cmdtype_set(attr, APR_PROGRAM);
    apr_procattr_detach_set(attr, 1);
    if (((rv = apr_filepath_get(&cwd, 0, ptemp)) != APR_SUCCESS)
           || ((rv = apr_procattr_dir_set(attr, cwd)) != APR_SUCCESS)) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ap_server_conf, APLOGNO(00412)
                     "Parent: Failed to get the current path");
    }

    if (!args) {
        /* Build the args array, only once since it won't change
         * for the lifetime of this parent process.
         */
        if ((rv = ap_os_proc_filepath(&cmd, ptemp))
                != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, ERROR_BAD_PATHNAME, ap_server_conf, APLOGNO(00413)
                         "Parent: Failed to get full path of %s",
                         ap_server_conf->process->argv[0]);
            apr_pool_destroy(ptemp);
            return -1;
        }

