static void
authenticateAuthUserRequestSetIp(AuthUserRequest * auth_user_request, IpAddress &ipaddr)
{
    AuthUser *auth_user = auth_user_request->user();

    if (!auth_user)
        return;

    auth_user->addIp(ipaddr);
}