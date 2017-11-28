void
ClientRequestContext::checkNoCacheDone(int answer)
{
    acl_checklist = NULL;
    http->request->flags.cachable = answer;
    http->doCallouts();
}