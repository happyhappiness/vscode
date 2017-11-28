bool
BasicUser::authenticated() const
{
    if ((flags.credentials_ok == 1) && (credentials_checkedtime + basicConfig.credentialsTTL > squid_curtime))
        return true;

    debugs(29, 4, "User not authenticated or credentials need rechecking.");

    return false;
}