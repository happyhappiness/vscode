static RSA *
ssl_temp_rsa_cb(SSL * ssl, int anInt, int keylen)
{
    static RSA *rsa_512 = NULL;
    static RSA *rsa_1024 = NULL;
    RSA *rsa = NULL;
    int newkey = 0;

    switch (keylen) {

    case 512:

        if (!rsa_512) {
            rsa_512 = RSA_generate_key(512, RSA_F4, NULL, NULL);
            newkey = 1;
        }

        rsa = rsa_512;
        break;

    case 1024:

        if (!rsa_1024) {
            rsa_1024 = RSA_generate_key(1024, RSA_F4, NULL, NULL);
            newkey = 1;
        }

        rsa = rsa_1024;
        break;

    default:
        debugs(83, DBG_IMPORTANT, "ssl_temp_rsa_cb: Unexpected key length " << keylen);
        return NULL;
    }

    if (rsa == NULL) {
        debugs(83, DBG_IMPORTANT, "ssl_temp_rsa_cb: Failed to generate key " << keylen);
        return NULL;
    }

    if (newkey) {
        if (Debug::Enabled(83, 5))
            PEM_write_RSAPrivateKey(debug_log, rsa, NULL, NULL, 0, NULL, NULL);

        debugs(83, DBG_IMPORTANT, "Generated ephemeral RSA key of length " << keylen);
    }

    return rsa;
}