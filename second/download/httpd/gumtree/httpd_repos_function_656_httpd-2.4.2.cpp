static void ssl_tmp_keys_free(server_rec *s)
{
    SSLModConfigRec *mc = myModConfig(s);

    MODSSL_TMP_KEYS_FREE(mc, RSA);
    MODSSL_TMP_KEYS_FREE(mc, DH);
#ifndef OPENSSL_NO_EC
    MODSSL_TMP_KEY_FREE(mc, EC_KEY, SSL_TMP_KEY_EC_256);
#endif
}