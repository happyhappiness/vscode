void
ProxyAuthNeeded::checkForAsync(ACLChecklist *checklist) const
{
    /* Client is required to resend the request with correct authentication
     * credentials. (This may be part of a stateful auth protocol.)
     * The request is denied.
     */
    debugs(28, 6, "ACLChecklist::checkForAsync: requiring Proxy Auth header.");
    checklist->currentAnswer(ACCESS_REQ_PROXY_AUTH);
    checklist->changeState (ACLChecklist::NullState::Instance());
    checklist->markFinished();
}