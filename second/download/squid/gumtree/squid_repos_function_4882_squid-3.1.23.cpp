void
AuthBasicUserRequest::authenticate(HttpRequest * request, ConnStateData * conn, http_hdr_type type)
{
    assert(user() != NULL);

    basic_data *basic_auth = dynamic_cast<BasicUser *>(user());

    /* if the password is not ok, do an identity */

    if (!basic_auth || basic_auth->flags.credentials_ok != 1)
        return;

    /* are we about to recheck the credentials externally? */
    if ((basic_auth->credentials_checkedtime + basicConfig.credentialsTTL) <= squid_curtime) {
        debugs(29, 4, "authBasicAuthenticate: credentials expired - rechecking");
        return;
    }

    /* we have been through the external helper, and the credentials haven't expired */
    debugs(29, 9, "authenticateBasicAuthenticateuser: user '" << basic_auth->username() << "' authenticated");

    /* Decode now takes care of finding the AuthUser struct in the cache */
    /* after external auth occurs anyway */
    basic_auth->expiretime = current_time.tv_sec;

    return;
}