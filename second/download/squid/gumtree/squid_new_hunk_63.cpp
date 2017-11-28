void
ProxyAuthLookup::checkForAsync(ACLChecklist *cl)const
{
    ACLFilledChecklist *checklist = Filled(cl);

    checklist->asyncInProgress(true);
    debugs(28, 3, HERE << "checking password via authenticator");

    /* make sure someone created auth_user_request for us */
    assert(checklist->auth_user_request != NULL);
    assert(checklist->auth_user_request->valid());
    checklist->auth_user_request->start(LookupDone, checklist);
}

void
ProxyAuthLookup::LookupDone(void *data)
{
    ACLFilledChecklist *checklist = Filled(static_cast<ACLChecklist*>(data));

    assert (checklist->asyncState() == ProxyAuthLookup::Instance());

    if (checklist->auth_user_request == NULL || !checklist->auth_user_request->valid() || checklist->conn() == NULL) {
        /* credentials could not be checked either way
         * restart the whole process */
        /* OR the connection was closed, there's no way to continue */
        checklist->auth_user_request = NULL;

        if (checklist->conn() != NULL) {
            checklist->conn()->auth_user_request = NULL;
        }
    }

    checklist->asyncInProgress(false);
    checklist->changeState (ACLChecklist::NullState::Instance());
    checklist->matchNonBlocking();
}

void
ProxyAuthNeeded::checkForAsync(ACLChecklist *checklist) const
{
    /* Client is required to resend the request with correct authentication
