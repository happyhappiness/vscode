static void socache_dc_destroy(ap_socache_instance_t *ctx, server_rec *s)
{
    if (ctx && ctx->dc) {
        DC_CTX_free(ctx->dc);
        ctx->dc = NULL;
    }
}