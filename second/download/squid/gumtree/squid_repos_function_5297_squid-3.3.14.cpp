void
Auth::Digest::Config::fixHeader(Auth::UserRequest::Pointer auth_user_request, HttpReply *rep, http_hdr_type hdrType, HttpRequest * request)
{
    if (!authenticateProgram)
        return;

    int stale = 0;

    if (auth_user_request != NULL) {
        Auth::Digest::UserRequest *digest_request = dynamic_cast<Auth::Digest::UserRequest*>(auth_user_request.getRaw());
        assert (digest_request != NULL);

        stale = !digest_request->flags.invalid_password;
    }

    /* on a 407 or 401 we always use a new nonce */
    digest_nonce_h *nonce = authenticateDigestNonceNew();

    debugs(29, 9, HERE << "Sending type:" << hdrType <<
           " header: 'Digest realm=\"" << digestAuthRealm << "\", nonce=\"" <<
           authenticateDigestNonceNonceb64(nonce) << "\", qop=\"" << QOP_AUTH <<
           "\", stale=" << (stale ? "true" : "false"));

    /* in the future, for WWW auth we may want to support the domain entry */
    httpHeaderPutStrf(&rep->header, hdrType, "Digest realm=\"%s\", nonce=\"%s\", qop=\"%s\", stale=%s", digestAuthRealm, authenticateDigestNonceNonceb64(nonce), QOP_AUTH, stale ? "true" : "false");
}