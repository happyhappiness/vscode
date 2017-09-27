{
    const char *storename;
    apr_file_t *fp;
    apr_size_t nbytes = size;
    apr_status_t rv;

    storename = slotmem_filename(pool, name);

    if (storename) {
        rv = apr_file_open(&fp, storename, APR_READ | APR_WRITE, APR_OS_DEFAULT,
                           pool);
        if (rv == APR_SUCCESS) {
            apr_finfo_t fi;
