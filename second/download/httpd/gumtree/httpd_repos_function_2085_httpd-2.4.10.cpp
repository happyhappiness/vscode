static apr_status_t send_data(proxy_conn_rec *conn,
                              struct iovec *vec,
                              int nvec,
                              apr_size_t *len)
{
    apr_status_t rv = APR_SUCCESS;
    apr_size_t written = 0, to_write = 0;
    int i, offset;
    apr_socket_t *s = conn->sock;

    for (i = 0; i < nvec; i++) {
        to_write += vec[i].iov_len;
    }

    offset = 0;
    while (to_write) {
        apr_size_t n = 0;
        rv = apr_socket_sendv(s, vec + offset, nvec - offset, &n);
        if (rv != APR_SUCCESS) {
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

    conn->worker->s->transferred += written;
    *len = written;

    return rv;
}