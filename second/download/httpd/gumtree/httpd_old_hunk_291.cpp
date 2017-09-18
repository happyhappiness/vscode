    SSLModConfigRec *mc = myModConfig(s);

    MODSSL_TMP_KEYS_FREE(mc, RSA);
    MODSSL_TMP_KEYS_FREE(mc, DH);
}

static void ssl_tmp_key_init_rsa(server_rec *s,
                                 int bits, int idx)
{
    SSLModConfigRec *mc = myModConfig(s);

    if (!(mc->pTmpKeys[idx] =
          RSA_generate_key(bits, RSA_F4, NULL, NULL)))
    {
        ssl_log(s, SSL_LOG_ERROR,
                "Init: Failed to generate temporary "
                "%d bit RSA private key", bits);
        ssl_die();
    }

}

static void ssl_tmp_key_init_dh(server_rec *s,
                                int bits, int idx)
{
    SSLModConfigRec *mc = myModConfig(s);

    if (!(mc->pTmpKeys[idx] =
          ssl_dh_GetTmpParam(bits)))
    {
        ssl_log(s, SSL_LOG_ERROR,
                "Init: Failed to generate temporary "
                "%d bit DH parameters", bits);
        ssl_die();
    }
}

#define MODSSL_TMP_KEY_INIT_RSA(s, bits) \
    ssl_tmp_key_init_rsa(s, bits, SSL_TMP_KEY_RSA_##bits)

#define MODSSL_TMP_KEY_INIT_DH(s, bits) \
    ssl_tmp_key_init_dh(s, bits, SSL_TMP_KEY_DH_##bits)

static void ssl_tmp_keys_init(server_rec *s)
{
    ssl_log(s, SSL_LOG_INFO,
            "Init: Generating temporary RSA private keys (512/1024 bits)");

    MODSSL_TMP_KEY_INIT_RSA(s, 512);
    MODSSL_TMP_KEY_INIT_RSA(s, 1024);

    ssl_log(s, SSL_LOG_INFO,
            "Init: Generating temporary DH parameters (512/1024 bits)");

    MODSSL_TMP_KEY_INIT_DH(s, 512);
    MODSSL_TMP_KEY_INIT_DH(s, 1024);
}

/*
 *  Per-module initialization
 */
int ssl_init_Module(apr_pool_t *p, apr_pool_t *plog,
