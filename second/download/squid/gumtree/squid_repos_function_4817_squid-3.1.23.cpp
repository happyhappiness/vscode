void
authenticateAuthUserRequestRemoveIp(AuthUserRequest * auth_user_request, IpAddress const &ipaddr)
{
    AuthUser *auth_user = auth_user_request->user();

    if (!auth_user)
        return;

    auth_user->removeIp(ipaddr);
}