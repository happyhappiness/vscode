int
ACLMaxUserIP::match(Auth::UserRequest::Pointer auth_user_request, Ip::Address const &src_addr)
{
    /*
     * the logic for flush the ip list when the limit is hit vs keep
     * it sorted in most recent access order and just drop the oldest
     * one off is currently undecided (RBC)
     */

    if (authenticateAuthUserRequestIPCount(auth_user_request) <= maximum)
        return 0;

    debugs(28, DBG_IMPORTANT, "aclMatchUserMaxIP: user '" << auth_user_request->username() << "' tries to use too many IP addresses (max " << maximum << " allowed)!");

    /* this is a match */
    if (flags.isSet(ACL_F_STRICT)) {
        /*
         * simply deny access - the user name is already associated with
         * the request
         */
        /* remove _this_ ip, as it is the culprit for going over the limit */
        authenticateAuthUserRequestRemoveIp(auth_user_request, src_addr);
        debugs(28, 4, "aclMatchUserMaxIP: Denying access in strict mode");
    } else {
        /*
         * non-strict - remove some/all of the cached entries
         * ie to allow the user to move machines easily
         */
        authenticateAuthUserRequestClearIp(auth_user_request);
        debugs(28, 4, "aclMatchUserMaxIP: Denying access in non-strict mode - flushing the user ip cache");
    }

    return 1;
}