int
authenticateUserAuthenticated(Auth::UserRequest::Pointer auth_user_request)
{
    if (auth_user_request == NULL || !auth_user_request->valid())
        return 0;

    return auth_user_request->authenticated();
}