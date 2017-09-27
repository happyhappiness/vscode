        if (rv != APR_SUCCESS) {
            apr_file_remove(storename, slotmem->gpool);
        }
    }
}

static apr_status_t restore_slotmem(void *ptr, const char *storename,
                                    apr_size_t size, apr_pool_t *pool)
{
    apr_file_t *fp;
    apr_size_t nbytes = size;
    apr_status_t rv = APR_SUCCESS;
    unsigned char digest[APR_MD5_DIGESTSIZE];
    unsigned char digest2[APR_MD5_DIGESTSIZE];

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02335)
                 "restoring %s", storename);

    if (storename) {
        rv = apr_file_open(&fp, storename, APR_READ | APR_WRITE, APR_OS_DEFAULT,
                           pool);
