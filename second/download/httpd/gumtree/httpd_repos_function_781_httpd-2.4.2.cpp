void *ssl_config_perdir_create(apr_pool_t *p, char *dir)
{
    SSLDirConfigRec *dc = apr_palloc(p, sizeof(*dc));

    dc->bSSLRequired  = FALSE;
    dc->aRequirement  = apr_array_make(p, 4, sizeof(ssl_require_t));
    dc->nOptions      = SSL_OPT_NONE|SSL_OPT_RELSET;
    dc->nOptionsAdd   = SSL_OPT_NONE;
    dc->nOptionsDel   = SSL_OPT_NONE;

    dc->szCipherSuite          = NULL;
    dc->nVerifyClient          = SSL_CVERIFY_UNSET;
    dc->nVerifyDepth           = UNSET;

    dc->szCACertificatePath    = NULL;
    dc->szCACertificateFile    = NULL;
    dc->szUserName             = NULL;

    dc->nRenegBufferSize = UNSET;

    return dc;
}