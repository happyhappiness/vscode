static int ssl_tmp_keys_init(server_rec *s)
{
    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, s,
                 "Init: Generating temporary RSA private keys (512/1024 bits)");

    if (MODSSL_TMP_KEY_INIT_RSA(s, 512) ||
        MODSSL_TMP_KEY_INIT_RSA(s, 1024)) {
        return !OK;
    }

    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, s,
                 "Init: Generating temporary DH parameters (512/1024 bits)");

    if (MODSSL_TMP_KEY_INIT_DH(s, 512) ||
        MODSSL_TMP_KEY_INIT_DH(s, 1024)) {
        return !OK;
    }

#ifndef OPENSSL_NO_EC
    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, s,
                 "Init: Generating temporary EC parameters (256 bits)");

    if (MODSSL_TMP_KEY_INIT_EC(s, 256)) {
        return !OK;
    }
#endif

    return OK;
}