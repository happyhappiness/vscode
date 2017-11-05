static apr_status_t writev_nonblocking(apr_socket_t *s,
                                       struct iovec *vec, apr_size_t nvec,
                                       apr_bucket_brigade *bb,
                                       apr_size_t *cumulative_bytes_written,
                                       conn_rec *c)
{
    apr_status_t rv = APR_SUCCESS, arv;
    apr_size_t bytes_written = 0, bytes_to_write = 0;
    apr_size_t i, offset;
    apr_interval_time_t old_timeout;

    arv = apr_socket_timeout_get(s, &old_timeout);
    if (arv != APR_SUCCESS) {
        return arv;
    }
    arv = apr_socket_timeout_set(s, 0);
    if (arv != APR_SUCCESS) {
        return arv;
    }

    for (i = 0; i < nvec; i++) {
        bytes_to_write += vec[i].iov_len;
    }
    offset = 0;
    while (bytes_written < bytes_to_write) {
        apr_size_t n = 0;
        rv = apr_socket_sendv(s, vec + offset, nvec - offset, &n);
        if (n > 0) {
            bytes_written += n;
            for (i = offset; i < nvec; ) {
                apr_bucket *bucket = APR_BRIGADE_FIRST(bb);
                if (APR_BUCKET_IS_METADATA(bucket)) {
                    APR_BUCKET_REMOVE(bucket);
                    apr_bucket_destroy(bucket);
                }
                else if (n >= vec[i].iov_len) {
                    APR_BUCKET_REMOVE(bucket);
                    apr_bucket_destroy(bucket);
                    offset++;
                    n -= vec[i++].iov_len;
                }
                else {
                    apr_bucket_split(bucket, n);
                    APR_BUCKET_REMOVE(bucket);
                    apr_bucket_destroy(bucket);
                    vec[i].iov_len -= n;
                    vec[i].iov_base = (char *) vec[i].iov_base + n;
                    break;
                }
            }
        }
        if (rv != APR_SUCCESS) {
            break;
        }
    }
    if ((ap__logio_add_bytes_out != NULL) && (bytes_written > 0)) {
        ap__logio_add_bytes_out(c, bytes_written);
    }
    *cumulative_bytes_written += bytes_written;

    arv = apr_socket_timeout_set(s, old_timeout);
    if ((arv != APR_SUCCESS) && (rv == APR_SUCCESS)) {
        return arv;
    }
    else {
        return rv;
    }
}