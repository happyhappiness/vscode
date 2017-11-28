digest_nonce_h *
Auth::Digest::User::currentNonce()
{
    digest_nonce_h *nonce = NULL;
    dlink_node *link = nonces.tail;
    if (link) {
        nonce = static_cast<digest_nonce_h *>(link->data);
        if (authDigestNonceIsStale(nonce))
            nonce = NULL;
    }
    return nonce;
}