void
authenticateAuthUserRequestClearIp(AuthUserRequest * auth_user_request)
{
    if (auth_user_request)
        auth_user_request->user()->clearIp();
}