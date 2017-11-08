static int pass_response(request_rec *r, proxy_conn_rec *conn)
{
    apr_bucket_brigade *bb;
    apr_bucket *b;
    const char *location;
    scgi_config *conf;
    socket_ex_data *sock_data;
    int status;

    sock_data = apr_palloc(r->pool, sizeof(*sock_data));
    sock_data->sock = conn->sock;
    sock_data->counter = &conn->worker->s->read;

    bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);
    b = bucket_socket_ex_create(sock_data, r->connection->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, b);
    b = apr_bucket_eos_create(r->connection->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, b);

    status = ap_scan_script_header_err_brigade(r, bb, NULL);
    if (status != OK) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "proxy: " PROXY_FUNCTION ": error reading response "
                      "headers from %s:%u", conn->hostname, conn->port);
        r->status_line = NULL;
        apr_brigade_destroy(bb);
        return status;
    }

    conf = ap_get_module_config(r->per_dir_config, &proxy_scgi_module);
    if (conf->sendfile && conf->sendfile != scgi_sendfile_off) {
        short err = 1;

        location = apr_table_get(r->err_headers_out, conf->sendfile);
        if (!location) {
            err = 0;
            location = apr_table_get(r->headers_out, conf->sendfile);
        }
        if (location) {
            scgi_request_config *req_conf = apr_palloc(r->pool,
                                                       sizeof(*req_conf));
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "proxy: " PROXY_FUNCTION ": Found %s: %s - "
                          "preparing subrequest.",
                          conf->sendfile, location);

            if (err) {
                apr_table_unset(r->err_headers_out, conf->sendfile);
            }
            else {
                apr_table_unset(r->headers_out, conf->sendfile);
            }
            req_conf->location = location;
            req_conf->type = scgi_sendfile;
            ap_set_module_config(r->request_config, &proxy_scgi_module,
                                 req_conf);
            apr_brigade_destroy(bb);
            return OK;
        }
    }

    if (conf->internal_redirect && r->status == HTTP_OK) {
        location = apr_table_get(r->headers_out, "Location");
        if (location && *location == '/') {
            scgi_request_config *req_conf = apr_palloc(r->pool,
                                                       sizeof(*req_conf));
            req_conf->location = location;
            req_conf->type = scgi_internal_redirect;
            ap_set_module_config(r->request_config, &proxy_scgi_module,
                                 req_conf);
            apr_brigade_destroy(bb);
            return OK;
        }
    }

    /* XXX: What could we do with that return code? */
    (void)ap_pass_brigade(r->output_filters, bb);

    return OK;
}