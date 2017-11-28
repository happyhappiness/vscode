void
Auth::Digest::UserRequest::addAuthenticationInfoTrailer(HttpReply * rep, int accel)
{
    int type;

    if (!auth_user_request)
        return;

    /* has the header already been send? */
    if (flags.authinfo_sent)
        return;

    /* don't add to authentication error pages */
    if ((!accel && rep->sline.status() == Http::scProxyAuthenticationRequired)
            || (accel && rep->sline.status() == Http::scUnauthorized))
        return;

    type = accel ? HDR_AUTHENTICATION_INFO : HDR_PROXY_AUTHENTICATION_INFO;

    if ((static_cast<Auth::Digest::Config*>(digestScheme::GetInstance()->getConfig())->authenticate) && authDigestNonceLastRequest(nonce)) {
        Auth::Digest::User *digest_user = dynamic_cast<Auth::Digest::User *>(auth_user_request->user().getRaw());
        nonce = digest_user->currentNonce();
        if (!nonce) {
            nonce = authenticateDigestNonceNew();
            authDigestUserLinkNonce(digest_user, nonce);
        }
        debugs(29, 9, "Sending type:" << type << " header: 'nextnonce=\"" << authenticateDigestNonceNonceb64(nonce) << "\"");
        httpTrailerPutStrf(&rep->header, type, "nextnonce=\"%s\"", authenticateDigestNonceNonceb64(nonce));
    }
}