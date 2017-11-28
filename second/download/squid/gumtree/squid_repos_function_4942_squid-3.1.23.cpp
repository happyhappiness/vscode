static const char *
authenticateDigestNonceNonceb64(digest_nonce_h * nonce)
{
    if (!nonce)
        return NULL;

    return (char const *) nonce->key;
}