void
authenticateAuthUserRequestClearIp(Auth::UserRequest::Pointer auth_user_request)
{
    if (auth_user_request != NULL)
        auth_user_request->user()->clearIp();
}