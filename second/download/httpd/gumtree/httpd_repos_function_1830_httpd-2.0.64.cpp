char *ap_rfc1413(conn_rec *conn, server_rec *srv)
{
    apr_socket_t *sock;
    apr_status_t rv;

    rv = rfc1413_connect(&sock, conn, srv);
    if (rv == APR_SUCCESS) {
        rv = rfc1413_query(sock, conn, srv);
        apr_socket_close(sock);
    }
    if (rv != APR_SUCCESS) {
        conn->remote_logname = FROM_UNKNOWN;
    }
    return conn->remote_logname;
}