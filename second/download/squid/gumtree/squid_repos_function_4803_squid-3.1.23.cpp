int
ACLProxyAuth::matchProxyAuth(ACLChecklist *cl)
{
    ACLFilledChecklist *checklist = Filled(cl);
    checkAuthForCaching(checklist);
    /* check to see if we have matched the user-acl before */
    int result = cacheMatchAcl(&checklist->auth_user_request->user()->
                               proxy_match_cache, checklist);
    AUTHUSERREQUESTUNLOCK(checklist->auth_user_request, "ACLChecklist via ACLProxyAuth");
    return result;
}