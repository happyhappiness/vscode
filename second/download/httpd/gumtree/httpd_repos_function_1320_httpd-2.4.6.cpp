static void socache_shmcb_destroy(ap_socache_instance_t *ctx, server_rec *s)
{
    if (ctx && ctx->shm) {
        apr_shm_destroy(ctx->shm);
        ctx->shm = NULL;
    }
}