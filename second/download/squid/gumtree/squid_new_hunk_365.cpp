    const AuthAclState result = Auth::UserRequest::tryToAuthenticateAndSetAuthUser(
                                    &checklist->auth_user_request, headertype, request,
                                    checklist->conn(), checklist->src_addr);
    switch (result) {

    case AUTH_ACL_CANNOT_AUTHENTICATE:
        debugs(28, 4, HERE << "returning " << ACCESS_DENIED << " user authenticated but not authorised.");
        return ACCESS_DENIED;

    case AUTH_AUTHENTICATED:
        return ACCESS_ALLOWED;
        break;

    case AUTH_ACL_HELPER:
        debugs(28, 4, HERE << "returning " << ACCESS_DUNNO << " sending credentials to helper.");
        checklist->changeState(ProxyAuthLookup::Instance());
        return ACCESS_DUNNO; // XXX: break this down into DUNNO, EXPIRED_OK, EXPIRED_BAD states

    case AUTH_ACL_CHALLENGE:
        debugs(28, 4, HERE << "returning " << ACCESS_AUTH_REQUIRED << " sending authentication challenge.");
        /* Client is required to resend the request with correct authentication
         * credentials. (This may be part of a stateful auth protocol.)
         * The request is denied.
         */
        return ACCESS_AUTH_REQUIRED;

    default:
        fatal("unexpected authenticateAuthenticate reply\n");
        return ACCESS_DENIED;
    }
}
