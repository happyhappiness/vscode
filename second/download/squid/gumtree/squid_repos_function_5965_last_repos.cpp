static digest_nonce_h *
authenticateDigestNonceFindNonce(const char *nonceb64)
{
    digest_nonce_h *nonce = NULL;

    if (nonceb64 == NULL)
        return NULL;

    debugs(29, 9, "looking for nonceb64 '" << nonceb64 << "' in the nonce cache.");

    nonce = static_cast < digest_nonce_h * >(hash_lookup(digest_nonce_cache, nonceb64));

    if ((nonce == NULL) || (strcmp(authenticateDigestNonceNonceb64(nonce), nonceb64)))
        return NULL;

    debugs(29, 9, "Found nonce '" << nonce << "'");

    return nonce;
}