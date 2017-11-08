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

    mctx->pphrase_dialog_type = SSL_PPTYPE_UNSET;
    mctx->pphrase_dialog_path = NULL;

    mctx->pkcs7               = NULL;
    mctx->cert_chain          = NULL;

    mctx->crl_path            = NULL;
    mctx->crl_file            = NULL;
    mctx->crl_check_mode      = SSL_CRLCHECK_UNSET;

    mctx->auth.ca_cert_path   = NULL;
    mctx->auth.ca_cert_file   = NULL;
    mctx->auth.cipher_suite   = NULL;
    mctx->auth.verify_depth   = UNSET;
    mctx->auth.verify_mode    = SSL_CVERIFY_UNSET;

    mctx->ocsp_enabled        = FALSE;
    mctx->ocsp_force_default  = FALSE;
    mctx->ocsp_responder      = NULL;
    mctx->ocsp_resptime_skew  = UNSET;
    mctx->ocsp_resp_maxage    = UNSET;
    mctx->ocsp_responder_timeout = UNSET;

#ifdef HAVE_OCSP_STAPLING
    mctx->stapling_enabled           = UNSET;
    mctx->stapling_resptime_skew     = UNSET;
    mctx->stapling_resp_maxage       = UNSET;
    mctx->stapling_cache_timeout     = UNSET;
    mctx->stapling_return_errors     = UNSET;
    mctx->stapling_fake_trylater     = UNSET;
    mctx->stapling_errcache_timeout  = UNSET;
    mctx->stapling_responder_timeout = UNSET;
    mctx->stapling_force_url         = NULL;
#endif

#ifdef HAVE_SRP
    mctx->srp_vfile =             NULL;
    mctx->srp_unknown_user_seed = NULL;
    mctx->srp_vbase =             NULL;
#endif
}