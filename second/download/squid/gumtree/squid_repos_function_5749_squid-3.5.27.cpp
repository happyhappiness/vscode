static void
authenticateAuthUserRequestSetIp(Auth::UserRequest::Pointer auth_user_request, Ip::Address &ipaddr)
{
    Auth::User::Pointer auth_user = auth_user_request->user();

    if (!auth_user)
        return;

    auth_user->addIp(ipaddr);
}