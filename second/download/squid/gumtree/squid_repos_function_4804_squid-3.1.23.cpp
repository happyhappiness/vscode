void
ACLProxyAuth::checkAuthForCaching(ACLChecklist *checklist)const
{
    /* for completeness */
    /* consistent parameters ? */
    assert(authenticateUserAuthenticated(Filled(checklist)->auth_user_request));
    /* this check completed */
}