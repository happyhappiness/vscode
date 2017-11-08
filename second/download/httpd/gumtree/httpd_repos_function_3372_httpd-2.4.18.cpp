static apr_status_t recv_data_full(const fcgi_provider_conf *conf,
                                   request_rec *r,
                                   apr_socket_t *s,
                                   char *buf,
                                   apr_size_t buflen)
{
    apr_size_t readlen;
    apr_size_t cumulative_len = 0;
    apr_status_t rv;

    do {
        readlen = buflen - cumulative_len;
        rv = recv_data(conf, r, s, buf + cumulative_len, &readlen);
        if (rv != APR_SUCCESS) {
            return rv;
        }
        cumulative_len += readlen;
    } while (cumulative_len < buflen);

    return APR_SUCCESS;
}