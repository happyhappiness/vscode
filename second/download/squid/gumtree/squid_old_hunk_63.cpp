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

void
ProxyAuthLookup::LookupDone(void *data, char *result)
{
    ACLFilledChecklist *checklist = Filled(static_cast<ACLChecklist*>(data));

    assert (checklist->asyncState() == ProxyAuthLookup::Instance());

    if (result != NULL)
        fatal("AclLookupProxyAuthDone: Old code floating around somewhere.\nMake clean and if that doesn't work, report a bug to the squid developers.\n");

    if (!authenticateValidateUser(checklist->auth_user_request) || checklist->conn() == NULL) {
        /* credentials could not be checked either way
         * restart the whole process */
        /* OR the connection was closed, there's no way to continue */
        AUTHUSERREQUESTUNLOCK(checklist->auth_user_request, "ProxyAuthLookup");

        if (checklist->conn() != NULL) {
            AUTHUSERREQUESTUNLOCK(checklist->conn()->auth_user_request, "conn via ProxyAuthLookup");	// DPW discomfort
            checklist->conn()->auth_type = AUTH_BROKEN;
        }
    }

    checklist->asyncInProgress(false);
    checklist->changeState (ACLChecklist::NullState::Instance());
    checklist->check();
}

void
ProxyAuthNeeded::checkForAsync(ACLChecklist *checklist) const
{
    /* Client is required to resend the request with correct authentication
