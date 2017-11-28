bool
Auth::Basic::User::authenticated() const
{
    if ((credentials() == Auth::Ok) && (expiretime + static_cast<Auth::Basic::Config*>(config)->credentialsTTL > squid_curtime))
        return true;

    debugs(29, 4, "User not authenticated or credentials need rechecking.");

    return false;
}