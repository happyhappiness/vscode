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