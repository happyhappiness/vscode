const char *
authenticateDigestNonceNonceb64(const digest_nonce_h * nonce)
{
    if (!nonce)
        return NULL;

    return (char const *) nonce->key;
}