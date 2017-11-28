void
ProxyAuthLookup::checkForAsync(ACLChecklist *cl)const
{
    ACLFilledChecklist *checklist = Filled(cl);

    checklist->asyncInProgress(true);
    debugs(28, 3, "ACLChecklist::checkForAsync: checking password via authenticator");

    AuthUserRequest *auth_user_request;
    /* make sure someone created auth_user_request for us */
    assert(checklist->auth_user_request != NULL);
    auth_user_request = checklist->auth_user_request;

    int validated = authenticateValidateUser(auth_user_request);
    assert(validated);
    auth_user_request->start(LookupDone, checklist);
}