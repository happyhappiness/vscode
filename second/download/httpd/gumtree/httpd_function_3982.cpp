static int sendall(proxy_conn_rec *conn, const char *buf, apr_size_t length,
                   request_rec *r)
{
    apr_status_t rv;
    apr_size_t written;

    while (length > 0) {
        written = length;
        if ((rv = apr_socket_send(conn->sock, buf, &written)) != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "proxy: " PROXY_FUNCTION ": sending data to "
                          "%s:%u failed", conn->hostname, conn->port);
            return HTTP_SERVICE_UNAVAILABLE;
        }

        /* count for stats */
        conn->worker->s->transferred += written;
        buf += written;
        length -= written;
    }

    return OK;
}