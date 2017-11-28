void
BasicUser::decode(char const *proxy_auth, AuthUserRequest *auth_user_request)
{
    currentRequest = auth_user_request;
    httpAuthHeader = proxy_auth;
    if (decodeCleartext ()) {
        extractUsername();
        extractPassword();
    }
    currentRequest = NULL;
    httpAuthHeader = NULL;
}