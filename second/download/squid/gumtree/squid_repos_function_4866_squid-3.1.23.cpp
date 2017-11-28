int
AuthNegotiateUserRequest::authenticated() const
{
    if (auth_state == AUTHENTICATE_STATE_DONE) {
        debugs(29, 9, "AuthNegotiateUserRequest::authenticated: user authenticated.");
        return 1;
    }

    debugs(29, 9, "AuthNegotiateUserRequest::authenticated: user not fully authenticated.");

    return 0;
}