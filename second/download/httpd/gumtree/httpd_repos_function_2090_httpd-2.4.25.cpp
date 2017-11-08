static
apr_status_t proxy_ftp_cleanup(request_rec *r, proxy_conn_rec *backend)
{

    backend->close = 1;
    ap_set_module_config(r->connection->conn_config, &proxy_ftp_module, NULL);
    ap_proxy_release_connection("FTP", backend, r->server);

    return OK;
}