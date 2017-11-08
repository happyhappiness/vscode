int ssl_callback_SRPServerParams(SSL *ssl, int *ad, void *arg)
{
    modssl_ctx_t *mctx = (modssl_ctx_t *)arg;
    char *username = SSL_get_srp_username(ssl);
    SRP_user_pwd *u;

    if (username == NULL
        || (u = SRP_VBASE_get_by_user(mctx->srp_vbase, username)) == NULL) {
        *ad = SSL_AD_UNKNOWN_PSK_IDENTITY;
        return SSL3_AL_FATAL;
    }

    if (SSL_set_srp_server_param(ssl, u->N, u->g, u->s, u->v, u->info) < 0) {
        *ad = SSL_AD_INTERNAL_ERROR;
        return SSL3_AL_FATAL;
    }

    /* reset all other options */
    SSL_set_verify(ssl, SSL_VERIFY_NONE,  ssl_callback_SSLVerify);
    return SSL_ERROR_NONE;
}