static apr_status_t get_data_full(proxy_conn_rec *conn,
                                  char *buffer,
                                  apr_size_t buflen)
{
    apr_size_t readlen;
    apr_size_t cumulative_len = 0;
    apr_status_t rv;

    do {
        readlen = buflen - cumulative_len;
        rv = get_data(conn, buffer + cumulative_len, &readlen);
        if (rv != APR_SUCCESS) {
            return rv;
        }
        cumulative_len += readlen;
    } while (cumulative_len < buflen);

    return APR_SUCCESS;
}