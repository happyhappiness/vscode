    struct iovec iov;
    conn_rec *c = r->connection;
    apr_bucket_brigade *bb = apr_brigade_create(r->pool, c->bucket_alloc);
    perchild_server_conf *sconf = (perchild_server_conf *)
                            ap_get_module_config(r->server->module_config, 
                                                 &mpm_perchild_module);
    char *foo = NULL;
    apr_size_t len;

/* XXX apr_get_brigade(..., AP_MODE_EXHAUSTIVE);  RBB */
/* foo = brigade_to_string() */
    len = strlen(foo);

    apr_os_sock_get(&sfd, thesock);

    iov.iov_base = NULL;
    iov.iov_len = 0;

    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

