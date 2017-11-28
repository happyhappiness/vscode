EVP_PKEY * Ssl::createSslPrivateKey()
{
    Ssl::EVP_PKEY_Pointer pkey(EVP_PKEY_new());

    if (!pkey)
        return NULL;

    Ssl::RSA_Pointer rsa(RSA_generate_key(1024, RSA_F4, NULL, NULL));

    if (!rsa)
        return NULL;

    if (!EVP_PKEY_assign_RSA(pkey.get(), (rsa.get())))
        return NULL;

    rsa.release();
    return pkey.release();
}