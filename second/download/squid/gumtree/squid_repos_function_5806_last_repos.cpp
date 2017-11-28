void
Auth::Basic::UserRequest::authenticate(HttpRequest *, ConnStateData *, Http::HdrType)
{
    assert(user() != NULL);

    /* if the password is not ok, do an identity */
    if (!user() || user()->credentials() != Auth::Ok)
        return;

    /* are we about to recheck the credentials externally? */
    if ((user()->expiretime + static_cast<Auth::Basic::Config*>(Auth::Config::Find("basic"))->credentialsTTL) <= squid_curtime) {
        debugs(29, 4, HERE << "credentials expired - rechecking");
        return;
    }

    /* we have been through the external helper, and the credentials haven't expired */
    debugs(29, 9, HERE << "user '" << user()->username() << "' authenticated");

    /* Decode now takes care of finding the AuthUser struct in the cache */
    /* after external auth occurs anyway */
    user()->expiretime = current_time.tv_sec;
}