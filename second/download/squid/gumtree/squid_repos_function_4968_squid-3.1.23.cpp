static void
authDigestUserLinkNonce(DigestUser * user, digest_nonce_h * nonce)
{
    dlink_node *node;
    digest_user_h *digest_user;

    if (!user || !nonce)
        return;

    digest_user = user;

    node = digest_user->nonces.head;

    while (node && (node->data != nonce))
        node = node->next;

    if (node)
        return;

    node = dlinkNodeNew();

    dlinkAddTail(nonce, node, &digest_user->nonces);

    authDigestNonceLink(nonce);

    /* ping this nonce to this auth user */
    assert((nonce->user == NULL) || (nonce->user == user));

    /* we don't lock this reference because removing the user removes the
     * hash too. Of course if that changes we're stuffed so read the code huh?
     */
    nonce->user = user;
}