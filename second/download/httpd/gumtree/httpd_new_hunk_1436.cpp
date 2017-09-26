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

