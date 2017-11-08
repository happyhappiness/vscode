static int scgi_handler(request_rec *r, proxy_worker *worker,
                        proxy_server_conf *conf, char *url,
                        const char *proxyname, apr_port_t proxyport)
{
    int status;
    proxy_conn_rec *backend = NULL;
    apr_pool_t *p = r->pool;
    apr_uri_t *uri;
    char dummy;

    if (strncasecmp(url, SCHEME "://", sizeof(SCHEME) + 2)) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00865)
                      "declining URL %s", url);
        return DECLINED;
    }

    /* Create space for state information */
    status = ap_proxy_acquire_connection(PROXY_FUNCTION, &backend, worker,
                                         r->server);
    if (status != OK) {
        goto cleanup;
    }
    backend->is_ssl = 0;

    /* Step One: Determine Who To Connect To */
    uri = apr_palloc(p, sizeof(*uri));
    status = ap_proxy_determine_connection(p, r, conf, worker, backend,
                                           uri, &url, proxyname, proxyport,
                                           &dummy, 1);
    if (status != OK) {
        goto cleanup;
    }

    /* Step Two: Make the Connection */
    if (ap_proxy_connect_backend(PROXY_FUNCTION, backend, worker, r->server)) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00866)
                      "failed to make connection to backend: %s:%u",
                      backend->hostname, backend->port);
        status = HTTP_SERVICE_UNAVAILABLE;
        goto cleanup;
    }

    /* Step Three: Process the Request */
    if (   ((status = ap_setup_client_block(r, REQUEST_CHUNKED_ERROR)) != OK)
        || ((status = send_headers(r, backend)) != OK)
        || ((status = send_request_body(r, backend)) != OK)
        || ((status = pass_response(r, backend)) != OK)) {
        goto cleanup;
    }

cleanup:
    if (backend) {
        backend->close = 1; /* always close the socket */
        ap_proxy_release_connection(PROXY_FUNCTION, backend, r->server);
    }
    return status;
}