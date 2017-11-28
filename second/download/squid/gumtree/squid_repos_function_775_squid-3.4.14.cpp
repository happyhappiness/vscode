void
ClientRequestContext::checkNoCacheDone(const allow_t &answer)
{
    acl_checklist = NULL;
    http->request->flags.cachable = (answer == ACCESS_ALLOWED);
    http->doCallouts();
}