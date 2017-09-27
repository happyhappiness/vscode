{
    const char *storename;
    apr_file_t *fp;
    apr_size_t nbytes = size;
    apr_status_t rv;

    storename = slotmem_filename(pool, name, 1);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02335)
                 "restoring %s", storename);

    if (storename) {
        rv = apr_file_open(&fp, storename, APR_READ | APR_WRITE, APR_OS_DEFAULT,
                           pool);
        if (rv == APR_SUCCESS) {
            apr_finfo_t fi;
