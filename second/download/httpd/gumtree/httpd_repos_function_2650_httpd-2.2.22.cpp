static apr_status_t read_from(apr_file_t *f, void *buf, 
             apr_off_t off, apr_size_t len)
{
    apr_status_t status;

    if ((status = apr_file_seek(f, APR_SET, &off)) != APR_SUCCESS ||
        ((status = apr_file_read_full(f, buf, len, NULL)) != APR_SUCCESS)) {
        /* if EOF is reached, pretend we read all zero's */
        if (status == APR_EOF) {
            memset(buf, 0, len);
            status = APR_SUCCESS;
        }
    }

    return status;
}