    struct iovec iov;
    conn_rec *c = r->connection;
    apr_bucket_brigade *bb = apr_brigade_create(r->pool, c->bucket_alloc);
    perchild_server_conf *sconf = (perchild_server_conf *)
                            ap_get_module_config(r->server->module_config, 
                                                 &mpm_perchild_module);
    char request_body[HUGE_STRING_LEN];
    apr_off_t len = 0;
    apr_size_t l = 0;
    perchild_header h;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, 
                 "passing request to another child.  Vhost: %s, child %d",
                 apr_table_get(r->headers_in, "Host"), child_num);
    ap_get_brigade(r->input_filters, bb, AP_MODE_EXHAUSTIVE, APR_NONBLOCK_READ,
                   len);
    if (apr_brigade_flatten(bb, request_body, &l) != APR_SUCCESS) {
        return DECLINED;
    }

    apr_os_sock_get(&sfd, thesock);

    iov.iov_base = "FOOBAR";
    iov.iov_len = 1;

    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

