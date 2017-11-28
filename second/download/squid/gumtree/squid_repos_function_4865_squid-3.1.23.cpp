AuthUserRequest *
AuthNegotiateConfig::decode(char const *proxy_auth)
{
    NegotiateUser *newUser = new NegotiateUser(&negotiateConfig);
    AuthNegotiateUserRequest *auth_user_request = new AuthNegotiateUserRequest ();
    assert(auth_user_request->user() == NULL);
    auth_user_request->user(newUser);
    auth_user_request->user()->auth_type = AUTH_NEGOTIATE;
    auth_user_request->user()->addRequest(auth_user_request);

    /* all we have to do is identify that it's Negotiate - the helper does the rest */
    debugs(29, 9, "AuthNegotiateConfig::decode: Negotiate authentication");
    return auth_user_request;
}