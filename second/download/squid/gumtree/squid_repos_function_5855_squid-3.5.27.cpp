Auth::UserRequest::Pointer
Auth::Ntlm::Config::decode(char const *proxy_auth, const char *aRequestRealm)
{
    Auth::Ntlm::User *newUser = new Auth::Ntlm::User(Auth::Config::Find("ntlm"), aRequestRealm);
    Auth::UserRequest::Pointer auth_user_request = new Auth::Ntlm::UserRequest();
    assert(auth_user_request->user() == NULL);

    auth_user_request->user(newUser);
    auth_user_request->user()->auth_type = Auth::AUTH_NTLM;

    auth_user_request->user()->BuildUserKey(proxy_auth, aRequestRealm);

    /* all we have to do is identify that it's NTLM - the helper does the rest */
    debugs(29, 9, HERE << "decode: NTLM authentication");
    return auth_user_request;
}