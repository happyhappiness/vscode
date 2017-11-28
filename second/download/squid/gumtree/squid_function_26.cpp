int
ACLFilledChecklist::authenticated()
{
    http_hdr_type headertype;

    if (NULL == request) {
        fatal ("requiresRequest SHOULD have been true for this ACL!!");
        return 0;
    } else if (request->flags.accelerated) {
        /* WWW authorization on accelerated requests */
        headertype = HDR_AUTHORIZATION;
    } else if (request->flags.intercepted || request->flags.spoof_client_ip) {
        debugs(28, DBG_IMPORTANT, HERE << " authentication not applicable on intercepted requests.");
        return -1;
    } else {
        /* Proxy authorization on proxy requests */
        headertype = HDR_PROXY_AUTHORIZATION;
    }

    /* get authed here */
    /* Note: this fills in auth_user_request when applicable */
    /*
     * DPW 2007-05-08
     * tryToAuthenticateAndSetAuthUser used to try to lock and
     * unlock auth_user_request on our behalf, but it was too
     * ugly and hard to follow.  Now we do our own locking here.
     *
     * I'm not sure what tryToAuthenticateAndSetAuthUser does when
     * auth_user_request is set before calling.  I'm tempted to
     * unlock and set it to NULL, but it seems safer to save the
     * pointer before calling and unlock it afterwards.  If the
     * pointer doesn't change then its a no-op.
     */
    AuthUserRequest *old_auth_user_request = auth_user_request;
    auth_acl_t result = AuthUserRequest::tryToAuthenticateAndSetAuthUser (&auth_user_request, headertype, request, conn(), src_addr);
    if (auth_user_request)
        AUTHUSERREQUESTLOCK(auth_user_request, "ACLFilledChecklist");
    AUTHUSERREQUESTUNLOCK(old_auth_user_request, "old ACLFilledChecklist");
    switch (result) {

    case AUTH_ACL_CANNOT_AUTHENTICATE:
        debugs(28, 4, "aclMatchAcl: returning  0 user authenticated but not authorised.");
        return 0;

    case AUTH_AUTHENTICATED:

        return 1;
        break;

    case AUTH_ACL_HELPER:
        debugs(28, 4, "aclMatchAcl: returning 0 sending credentials to helper.");
        changeState (ProxyAuthLookup::Instance());
        return 0;

    case AUTH_ACL_CHALLENGE:
        debugs(28, 4, "aclMatchAcl: returning 0 sending authentication challenge.");
        changeState (ProxyAuthNeeded::Instance());
        return 0;

    default:
        fatal("unexpected authenticateAuthenticate reply\n");
        return 0;
    }
}