EVP_PKEY * Ssl::createSslPrivateKey()
{
    Ssl::EVP_PKEY_Pointer pkey(EVP_PKEY_new());

    if (!pkey)
        return NULL;

    BIGNUM_Pointer bn(BN_new());
    if (!bn)
        return NULL;

    if (!BN_set_word(bn.get(), RSA_F4))
        return NULL;

    Ssl::RSA_Pointer rsa(RSA_new());
    if (!rsa)
        return NULL;

    int num = 2048; // Maybe use 4096 RSA keys, or better make it configurable?
    if (!RSA_generate_key_ex(rsa.get(), num, bn.get(), NULL))
        return NULL;

    if (!rsa)
        return NULL;

    if (!EVP_PKEY_assign_RSA(pkey.get(), (rsa.get())))
        return NULL;

    rsa.release();
    return pkey.release();
}