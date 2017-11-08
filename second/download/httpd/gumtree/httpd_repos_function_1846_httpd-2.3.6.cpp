static apr_status_t get_data(proxy_conn_rec *conn,
                             char *buffer,
                             apr_size_t *buflen)
{
    apr_status_t rv = apr_socket_recv(conn->sock, buffer, buflen);

    if (rv == APR_SUCCESS) {
        conn->worker->s->read += *buflen;
    }

    return rv;
}