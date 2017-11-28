AuthUserRequest *
AuthNTLMConfig::decode(char const *proxy_auth)
{
    NTLMUser *newUser = new NTLMUser(&ntlmConfig);
    AuthNTLMUserRequest *auth_user_request = new AuthNTLMUserRequest ();
    assert(auth_user_request->user() == NULL);
    auth_user_request->user(newUser);
    auth_user_request->user()->auth_type = AUTH_NTLM;
    auth_user_request->user()->addRequest(auth_user_request);

    /* all we have to do is identify that it's NTLM - the helper does the rest */
    debugs(29, 9, "AuthNTLMConfig::decode: NTLM authentication");
    return auth_user_request;
}