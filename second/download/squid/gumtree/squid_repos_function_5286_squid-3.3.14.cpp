void
authDigestNonceUnlink(digest_nonce_h * nonce)
{
    assert(nonce != NULL);

    if (nonce->references > 0) {
        -- nonce->references;
    } else {
        debugs(29, DBG_IMPORTANT, "authDigestNonceUnlink; Attempt to lower nonce " << nonce << " refcount below 0!");
    }

    debugs(29, 9, "authDigestNonceUnlink: nonce '" << nonce << "' now at '" << nonce->references << "'.");

    if (nonce->references == 0)
        authenticateDigestNonceDelete(nonce);
}