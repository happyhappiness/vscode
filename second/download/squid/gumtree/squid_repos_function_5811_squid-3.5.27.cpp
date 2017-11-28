Auth::Direction
Auth::Basic::UserRequest::module_direction()
{
    /* null auth_user is checked for by Auth::UserRequest::direction() */
    if (user()->auth_type != Auth::AUTH_BASIC)
        return Auth::CRED_ERROR;

    switch (user()->credentials()) {

    case Auth::Unchecked:
    case Auth::Pending:
        return Auth::CRED_LOOKUP;

    case Auth::Ok:
        if (user()->expiretime + static_cast<Auth::Basic::Config*>(Auth::Config::Find("basic"))->credentialsTTL <= squid_curtime)
            return Auth::CRED_LOOKUP;
        return Auth::CRED_VALID;

    case Auth::Failed:
        return Auth::CRED_VALID;

    default:
        return Auth::CRED_ERROR;
    }
}