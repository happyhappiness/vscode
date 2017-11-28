static void
authDigestNonceLink(digest_nonce_h * nonce)
{
    assert(nonce != NULL);
    ++nonce->references;
    debugs(29, 9, "authDigestNonceLink: nonce '" << nonce << "' now at '" << nonce->references << "'.");
}