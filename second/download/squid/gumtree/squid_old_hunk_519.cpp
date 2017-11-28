void
Auth::Digest::UserRequest::addAuthenticationInfoHeader(HttpReply * rep, int accel)
{
    http_hdr_type type;

    /* don't add to authentication error pages */

    if ((!accel && rep->sline.status == HTTP_PROXY_AUTHENTICATION_REQUIRED)
            || (accel && rep->sline.status == HTTP_UNAUTHORIZED))
        return;

    type = accel ? HDR_AUTHENTICATION_INFO : HDR_PROXY_AUTHENTICATION_INFO;

#if WAITING_FOR_TE
    /* test for http/1.1 transfer chunked encoding */
    if (chunkedtest)
        return;
#endif

    if ((static_cast<Auth::Digest::Config*>(Auth::Config::Find("digest"))->authenticateProgram) && authDigestNonceLastRequest(nonce)) {
        flags.authinfo_sent = 1;
        debugs(29, 9, HERE << "Sending type:" << type << " header: 'nextnonce=\"" << authenticateDigestNonceNonceb64(nonce) << "\"");
        httpHeaderPutStrf(&rep->header, type, "nextnonce=\"%s\"", authenticateDigestNonceNonceb64(nonce));
    }
}

#if WAITING_FOR_TE
void
Auth::Digest::UserRequest::addAuthenticationInfoTrailer(HttpReply * rep, int accel)
