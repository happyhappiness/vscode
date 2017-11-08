static conn_rec *x_create_connection(apr_pool_t *p, server_rec *server,
                                     apr_socket_t *csd, long conn_id,
                                     void *sbh, apr_bucket_alloc_t *alloc)
{
    trace_nocontext(p, __FILE__, __LINE__, "x_create_connection()");
    return NULL;
}