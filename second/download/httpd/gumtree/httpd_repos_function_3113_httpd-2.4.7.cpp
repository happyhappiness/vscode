static const char *sha1_func(ap_expr_eval_ctx_t *ctx, const void *data,
                               const char *arg)
{
    apr_sha1_ctx_t context;
    apr_byte_t sha1[APR_SHA1_DIGESTSIZE];
    char *out;

    out = apr_palloc(ctx->p, APR_SHA1_DIGESTSIZE*2+1);

    apr_sha1_init(&context);
    apr_sha1_update(&context, arg, strlen(arg));
    apr_sha1_final(sha1, &context);

    ap_bin2hex(sha1, APR_SHA1_DIGESTSIZE, out);

    return out;
}