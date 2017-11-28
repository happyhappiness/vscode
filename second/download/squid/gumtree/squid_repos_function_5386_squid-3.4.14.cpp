static void
authDigestNonceUserUnlink(digest_nonce_h * nonce)
{
    Auth::Digest::User *digest_user;
    dlink_node *link, *tmplink;

    if (!nonce)
        return;

    if (!nonce->user)
        return;

    digest_user = nonce->user;

    /* unlink from the user list. Yes we're crossing structures but this is the only
     * time this code is needed
     */
    link = digest_user->nonces.head;

    while (link) {
        tmplink = link;
        link = link->next;

        if (tmplink->data == nonce) {
            dlinkDelete(tmplink, &digest_user->nonces);
            authDigestNonceUnlink(static_cast < digest_nonce_h * >(tmplink->data));
            dlinkNodeDelete(tmplink);
            link = NULL;
        }
    }

    /* this reference to user was not locked because freeeing the user frees
     * the nonce too.
     */
    nonce->user = NULL;
}