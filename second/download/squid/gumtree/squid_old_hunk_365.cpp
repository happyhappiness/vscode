    const AuthAclState result = Auth::UserRequest::tryToAuthenticateAndSetAuthUser(
                                    &checklist->auth_user_request, headertype, request,
                                    checklist->conn(), checklist->src_addr);
    switch (result) {

    case AUTH_ACL_CANNOT_AUTHENTICATE:
        debugs(28, 4, HERE << "returning  0 user authenticated but not authorised.");
        return 0;

    case AUTH_AUTHENTICATED:
        return 1;
        break;

    case AUTH_ACL_HELPER:
        debugs(28, 4, HERE << "returning 0 sending credentials to helper.");
        checklist->changeState(ProxyAuthLookup::Instance());
        return 0;

    case AUTH_ACL_CHALLENGE:
        debugs(28, 4, HERE << "returning 0 sending authentication challenge.");
        checklist->changeState (ProxyAuthNeeded::Instance());
        return 0;

    default:
        fatal("unexpected authenticateAuthenticate reply\n");
        return 0;
    }
}
