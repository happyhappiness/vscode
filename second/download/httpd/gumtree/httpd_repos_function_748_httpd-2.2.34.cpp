static void modssl_ctx_init(modssl_ctx_t *mctx)
{
    mctx->sc                  = NULL; /* set during module init */

    mctx->ssl_ctx             = NULL; /* set during module init */

    mctx->pks                 = NULL;
    mctx->pkp                 = NULL;

#ifdef HAVE_TLS_SESSION_TICKETS
    mctx->ticket_key          = NULL;
#endif

    mctx->protocol            = SSL_PROTOCOL_ALL;
    mctx->protocol_set        = 0;

    mctx->pphrase_dialog_type = SSL_PPTYPE_UNSET;
    mctx->pphrase_dialog_path = NULL;

    mctx->cert_chain          = NULL;

    mctx->crl_path            = NULL;
    mctx->crl_file            = NULL;
    mctx->crl                 = NULL; /* set during module init */

    mctx->auth.ca_cert_path   = NULL;
    mctx->auth.ca_cert_file   = NULL;
    mctx->auth.cipher_suite   = NULL;
    mctx->auth.verify_depth   = UNSET;
    mctx->auth.verify_mode    = SSL_CVERIFY_UNSET;
}