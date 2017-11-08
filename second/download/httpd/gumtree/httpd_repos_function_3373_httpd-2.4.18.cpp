static apr_status_t sendv_data(const fcgi_provider_conf *conf,
                               request_rec *r,
                               apr_socket_t *s,
                               struct iovec *vec,
                               int nvec,
                               apr_size_t *len)
{
    apr_size_t to_write = 0, written = 0;
    apr_status_t rv = APR_SUCCESS;
    int i, offset;

    for (i = 0; i < nvec; i++) {
        to_write += vec[i].iov_len;
#if AP_MODULE_MAGIC_AT_LEAST(20130702,2) 
        ap_log_rdata(APLOG_MARK, APLOG_TRACE5, r, "FastCGI data sent",
                     vec[i].iov_base, vec[i].iov_len, AP_LOG_DATA_SHOW_OFFSET);
#endif
    }

    offset = 0;
    while (to_write) {
        apr_size_t n = 0;
        rv = apr_socket_sendv(s, vec + offset, nvec - offset, &n);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          APLOGNO(02498) "Sending data to %s failed",
                          conf->backend);
            break;
        }
        if (n > 0) {
            written += n;
            if (written >= to_write)
                break;                 /* short circuit out */
            for (i = offset; i < nvec; ) {
                if (n >= vec[i].iov_len) {
                    offset++;
                    n -= vec[i++].iov_len;
                } else {
                    vec[i].iov_len -= n;
                    vec[i].iov_base = (char *) vec[i].iov_base + n;
                    break;
                }
            }
        }
    }

    *len = written;

    return rv;
}