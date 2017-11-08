static void socache_dbm_destroy(ap_socache_instance_t *ctx, server_rec *s)
{
    /* the correct way */
    unlink(apr_pstrcat(ctx->pool, ctx->data_file, DBM_FILE_SUFFIX_DIR, NULL));
    unlink(apr_pstrcat(ctx->pool, ctx->data_file, DBM_FILE_SUFFIX_PAG, NULL));
    /* the additional ways to be sure */
    unlink(apr_pstrcat(ctx->pool, ctx->data_file, ".dir", NULL));
    unlink(apr_pstrcat(ctx->pool, ctx->data_file, ".pag", NULL));
    unlink(apr_pstrcat(ctx->pool, ctx->data_file, ".db", NULL));
    unlink(ctx->data_file);
}