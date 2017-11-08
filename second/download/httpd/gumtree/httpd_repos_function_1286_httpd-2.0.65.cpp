static
apr_status_t ap_proxy_http_cleanup(request_rec *r, proxy_http_conn_t *p_conn,
                                   proxy_conn_rec *backend) {
    /* If there are no KeepAlives, or if the connection has been signalled
     * to close, close the socket and clean up
     */

    /* if the connection is < HTTP/1.1, or Connection: close,
     * we close the socket, otherwise we leave it open for KeepAlive support
     */
    if (p_conn->close || (r->proto_num < HTTP_VERSION(1,1))) {
        if (p_conn->sock) {
            apr_socket_close(p_conn->sock);
            p_conn->sock = NULL;
            backend->connection = NULL;
        }
    }
    return OK;
}