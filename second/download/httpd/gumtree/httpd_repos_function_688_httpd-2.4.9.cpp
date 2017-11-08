static void ssl_init_ctx_cleanup(modssl_ctx_t *mctx)
{
    MODSSL_CFG_ITEM_FREE(SSL_CTX_free, mctx->ssl_ctx);

#ifdef HAVE_SRP
    if (mctx->srp_vbase != NULL) {
        SRP_VBASE_free(mctx->srp_vbase);
        mctx->srp_vbase = NULL;
    }
#endif
}