static apr_array_header_t *expr_peer_ext_list_fn(ap_expr_eval_ctx_t *ctx,
                                                 const void *dummy,
                                                 const char *arg)
{
    return ssl_ext_list(ctx->p, ctx->c, 1, arg);
}