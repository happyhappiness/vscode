static apr_status_t restore_slotmem(void *ptr, const char *name, apr_size_t size,
                                    apr_pool_t *pool)
{
    const char *storename;
    apr_file_t *fp;
    apr_size_t nbytes = size;
    apr_status_t rv = APR_SUCCESS;
    unsigned char digest[APR_MD5_DIGESTSIZE];
    unsigned char digest2[APR_MD5_DIGESTSIZE];

    storename = slotmem_filename(pool, name, 1);

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(02335)
                 "restoring %s", storename);

    if (storename) {
        rv = apr_file_open(&fp, storename, APR_READ | APR_WRITE, APR_OS_DEFAULT,
                           pool);
        if (rv == APR_SUCCESS) {
            rv = apr_file_read(fp, ptr, &nbytes);
            if ((rv == APR_SUCCESS || rv == APR_EOF) && nbytes == size) {
                rv = APR_SUCCESS;   /* for successful return @ EOF */
                /*
                 * if at EOF, don't bother checking md5
                 *  - backwards compatibility
                 *  */
                if (apr_file_eof(fp) != APR_EOF) {
                    apr_size_t ds = APR_MD5_DIGESTSIZE;
                    rv = apr_file_read(fp, digest, &ds);
                    if ((rv == APR_SUCCESS || rv == APR_EOF) &&
                        ds == APR_MD5_DIGESTSIZE) {
                        rv = APR_SUCCESS;
                        apr_md5(digest2, ptr, nbytes);
                        if (memcmp(digest, digest2, APR_MD5_DIGESTSIZE)) {
                            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                                         APLOGNO(02551) "bad md5 match");
                            rv = APR_EGENERAL;
                        }
                    }
                }
                else {
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                                 APLOGNO(02552) "at EOF... bypassing md5 match check (old persist file?)");
                }
            }
            else if (nbytes != size) {
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf,
                             APLOGNO(02553) "Expected %" APR_SIZE_T_FMT ": Read %" APR_SIZE_T_FMT,
                             size, nbytes);
                rv = APR_EGENERAL;
            }
            apr_file_close(fp);
        }
    }
    return rv;
}