static serf_bucket_t* conn_setup(apr_socket_t *sock,
                                 void *setup_baton,
                                 apr_pool_t *pool)
{
    serf_bucket_t *c;
    s_baton_t *ctx = setup_baton;

    c = serf_bucket_socket_create(sock, ctx->bkt_alloc);
    if (ctx->want_ssl) {
        c = serf_bucket_ssl_decrypt_create(c, ctx->ssl_ctx, ctx->bkt_alloc);
    }

    return c;
}