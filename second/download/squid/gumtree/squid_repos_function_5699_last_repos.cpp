int
ACLProxyAuth::matchProxyAuth(ACLChecklist *cl)
{
    ACLFilledChecklist *checklist = Filled(cl);
    if (checklist->request->flags.sslBumped)
        return 1; // AuthenticateAcl() already handled this bumped request
    if (!authenticateUserAuthenticated(Filled(checklist)->auth_user_request)) {
        return 0;
    }
    /* check to see if we have matched the user-acl before */
    int result = cacheMatchAcl(&checklist->auth_user_request->user()->proxy_match_cache, checklist);
    checklist->auth_user_request = NULL;
    return result;
}