void
authenticateAuthUserRequestRemoveIp(Auth::UserRequest::Pointer auth_user_request, Ip::Address const &ipaddr)
{
    Auth::User::Pointer auth_user = auth_user_request->user();

    if (!auth_user)
        return;

    auth_user->removeIp(ipaddr);
}