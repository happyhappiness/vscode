static
apr_status_t ap_proxy_http_cleanup(const char *scheme, request_rec *r,
                                   proxy_conn_rec *backend)
{
    /* If there are no KeepAlives, or if the connection has been signalled
     * to close, close the socket and clean up
     */

    /* if the connection is < HTTP/1.1, or Connection: close,
     * we close the socket, otherwise we leave it open for KeepAlive support
     */
    if (backend->close || (r->proto_num < HTTP_VERSION(1,1))) {
        backend->close_on_recycle = 1;
        ap_set_module_config(r->connection->conn_config, &proxy_http_module, NULL);
        ap_proxy_release_connection(scheme, backend, r->server);
    }
    return OK;
}