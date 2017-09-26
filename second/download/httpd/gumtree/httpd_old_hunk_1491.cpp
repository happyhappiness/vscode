
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                 "%s compiled against Server: %s, Library: %s",
                 modver, AP_SERVER_BASEVERSION, incver);
}


/*
 * Handle the Temporary RSA Keys and DH Params
 */

#define MODSSL_TMP_KEY_FREE(mc, type, idx) \
    if (mc->pTmpKeys[idx]) { \
        type##_free((type *)mc->pTmpKeys[idx]); \
        mc->pTmpKeys[idx] = NULL; \
    }

#define MODSSL_TMP_KEYS_FREE(mc, type) \
    MODSSL_TMP_KEY_FREE(mc, type, SSL_TMP_KEY_##type##_512); \
    MODSSL_TMP_KEY_FREE(mc, type, SSL_TMP_KEY_##type##_1024)

static void ssl_tmp_keys_free(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);

    MODSSL_TMP_KEYS_FREE(mc, RSA);
    MODSSL_TMP_KEYS_FREE(mc, DH);
#ifndef OPENSSL_NO_EC
    MODSSL_TMP_KEY_FREE(mc, EC_KEY, SSL_TMP_KEY_EC_256);
#endif
}

static int ssl_tmp_key_init_rsa(server_rec *s,
                                int bits, int idx)
{
    SSLModConfigRec *mc = myModConfig(s);

#ifdef HAVE_FIPS

    if (FIPS_mode() && bits < 1024) {
        mc->pTmpKeys[idx] = NULL;
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "Init: Skipping generating temporary "
                     "%d bit RSA private key in FIPS mode", bits);
        return OK;
    }

#endif

    if (!(mc->pTmpKeys[idx] =
          RSA_generate_key(bits, RSA_F4, NULL, NULL)))
    {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "Init: Failed to generate temporary "
                     "%d bit RSA private key", bits);
        ssl_log_ssl_error(APLOG_MARK, APLOG_ERR, s);
        return !OK;
    }

    return OK;
}

static int ssl_tmp_key_init_dh(server_rec *s,
                               int bits, int idx)
{
    SSLModConfigRec *mc = myModConfig(s);

#ifdef HAVE_FIPS

    if (FIPS_mode() && bits < 1024) {
        mc->pTmpKeys[idx] = NULL;
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s,
                     "Init: Skipping generating temporary "
                     "%d bit DH parameters in FIPS mode", bits);
        return OK;
    }

#endif

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

#ifndef OPENSSL_NO_EC
static int ssl_tmp_key_init_ec(server_rec *s,
                               int bits, int idx)
{
    SSLModConfigRec *mc = myModConfig(s);
    EC_KEY *ecdh = NULL;

    /* XXX: Are there any FIPS constraints we should enforce? */

    if (bits != 256) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "Init: Failed to generate temporary "
                     "%d bit EC parameters, only 256 bits supported", bits);
        return !OK;
    }

    if ((ecdh = EC_KEY_new()) == NULL ||
        EC_KEY_set_group(ecdh, EC_GROUP_new_by_curve_name(NID_X9_62_prime256v1)) != 1)
    {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                     "Init: Failed to generate temporary "
                     "%d bit EC parameters", bits);
        return !OK;
    }

    mc->pTmpKeys[idx] = ecdh;
    return OK;
}

#define MODSSL_TMP_KEY_INIT_EC(s, bits) \
    ssl_tmp_key_init_ec(s, bits, SSL_TMP_KEY_EC_##bits)

#endif

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

#ifndef OPENSSL_NO_EC
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, s,
                 "Init: Generating temporary EC parameters (256 bits)");

    if (MODSSL_TMP_KEY_INIT_EC(s, 256)) {
        return !OK;
    }
#endif

    return OK;
}

/*
 *  Per-module initialization
 */
int ssl_init_Module(apr_pool_t *p, apr_pool_t *plog,
                    apr_pool_t *ptemp,
                    server_rec *base_server)
