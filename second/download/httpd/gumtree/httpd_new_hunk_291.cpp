    SSLModConfigRec *mc = myModConfig(s);

    MODSSL_TMP_KEYS_FREE(mc, RSA);
    MODSSL_TMP_KEYS_FREE(mc, DH);
}

static int ssl_tmp_key_init_rsa(server_rec *s,
                                int bits, int idx)
{
    SSLModConfigRec *mc = myModConfig(s);

    if (!(mc->pTmpKeys[idx] =
          RSA_generate_key(bits, RSA_F4, NULL, NULL)))
    {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "Init: Failed to generate temporary "
                     "%d bit RSA private key", bits);
        return !OK;
    }

    return OK;
}

static int ssl_tmp_key_init_dh(server_rec *s,
                               int bits, int idx)
{
    SSLModConfigRec *mc = myModConfig(s);

    if (!(mc->pTmpKeys[idx] =
          ssl_dh_GetTmpParam(bits)))
    {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "Init: Failed to generate temporary "
                     "%d bit DH parameters", bits);
        return !OK;
    }

    return OK;
}

#define MODSSL_TMP_KEY_INIT_RSA(s, bits) \
    ssl_tmp_key_init_rsa(s, bits, SSL_TMP_KEY_RSA_##bits)

#define MODSSL_TMP_KEY_INIT_DH(s, bits) \
    ssl_tmp_key_init_dh(s, bits, SSL_TMP_KEY_DH_##bits)

static int ssl_tmp_keys_init(server_rec *s)
{
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                 "Init: Generating temporary RSA private keys (512/1024 bits)");

    if (MODSSL_TMP_KEY_INIT_RSA(s, 512) ||
        MODSSL_TMP_KEY_INIT_RSA(s, 1024)) {
        return !OK;
    }

    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                 "Init: Generating temporary DH parameters (512/1024 bits)");

    if (MODSSL_TMP_KEY_INIT_DH(s, 512) ||
        MODSSL_TMP_KEY_INIT_DH(s, 1024)) {
        return !OK;
    }

    return OK;
}

/*
 *  Per-module initialization
 */
int ssl_init_Module(apr_pool_t *p, apr_pool_t *plog,
