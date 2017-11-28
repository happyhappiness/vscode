Auth::UserRequest::Pointer
Auth::Ntlm::Config::decode(char const *proxy_auth)
{
    Auth::Ntlm::User *newUser = new Auth::Ntlm::User(Auth::Config::Find("ntlm"));
    Auth::UserRequest::Pointer auth_user_request = new Auth::Ntlm::UserRequest();
    assert(auth_user_request->user() == NULL);

    auth_user_request->user(newUser);
    auth_user_request->user()->auth_type = Auth::AUTH_NTLM;

    /* all we have to do is identify that it's NTLM - the helper does the rest */
    debugs(29, 9, HERE << "decode: NTLM authentication");
    return auth_user_request;
}