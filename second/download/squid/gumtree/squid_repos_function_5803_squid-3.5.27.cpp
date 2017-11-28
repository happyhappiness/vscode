Auth::UserRequest::Pointer
Auth::Negotiate::Config::decode(char const *proxy_auth, const char *aRequestRealm)
{
    Auth::Negotiate::User *newUser = new Auth::Negotiate::User(Auth::Config::Find("negotiate"), aRequestRealm);
    Auth::UserRequest *auth_user_request = new Auth::Negotiate::UserRequest();
    assert(auth_user_request->user() == NULL);

    auth_user_request->user(newUser);
    auth_user_request->user()->auth_type = Auth::AUTH_NEGOTIATE;

    auth_user_request->user()->BuildUserKey(proxy_auth, aRequestRealm);

    /* all we have to do is identify that it's Negotiate - the helper does the rest */
    debugs(29, 9, HERE << "decode Negotiate authentication");
    return auth_user_request;
}