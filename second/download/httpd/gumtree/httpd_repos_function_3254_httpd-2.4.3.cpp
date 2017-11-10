apr_status_t winnt_insert_network_bucket(conn_rec *c,
                                         apr_bucket_brigade *bb,
                                         apr_socket_t *socket)
{
    apr_bucket *e;
    winnt_conn_ctx_t *context = ap_get_module_config(c->conn_config,
                                                     &mpm_winnt_module);
    if (context == NULL || (e = context->overlapped.Pointer) == NULL)
        return AP_DECLINED;

    /* seed the brigade with AcceptEx read heap bucket */
    APR_BRIGADE_INSERT_HEAD(bb, e);
    /* also seed the brigade with the client socket. */
    e = apr_bucket_socket_create(socket, c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, e);
    return APR_SUCCESS;
}