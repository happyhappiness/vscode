void
Auth::Digest::Config::fixHeader(Auth::UserRequest::Pointer auth_user_request, HttpReply *rep, Http::HdrType hdrType, HttpRequest *)
{
    if (!authenticateProgram)
        return;

    bool stale = false;
    digest_nonce_h *nonce = NULL;

    /* on a 407 or 401 we always use a new nonce */
    if (auth_user_request != NULL) {
        Auth::Digest::User *digest_user = dynamic_cast<Auth::Digest::User *>(auth_user_request->user().getRaw());

        if (digest_user) {
            stale = digest_user->credentials() == Auth::Handshake;
            if (stale) {
                nonce = digest_user->currentNonce();
            }
        }
    }
    if (!nonce) {
        nonce = authenticateDigestNonceNew();
    }

    debugs(29, 9, "Sending type:" << hdrType <<
           " header: 'Digest realm=\"" << realm << "\", nonce=\"" <<
           authenticateDigestNonceNonceb64(nonce) << "\", qop=\"" << QOP_AUTH <<
           "\", stale=" << (stale ? "true" : "false"));

    /* in the future, for WWW auth we may want to support the domain entry */
    httpHeaderPutStrf(&rep->header, hdrType, "Digest realm=\"" SQUIDSBUFPH "\", nonce=\"%s\", qop=\"%s\", stale=%s",
                      SQUIDSBUFPRINT(realm), authenticateDigestNonceNonceb64(nonce), QOP_AUTH, stale ? "true" : "false");
}