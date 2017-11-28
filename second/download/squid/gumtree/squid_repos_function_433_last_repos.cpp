void
ClientRequestContext::checkNoCacheDone(const allow_t &answer)
{
    acl_checklist = NULL;
    if (answer.denied()) {
        http->request->flags.noCache = true; // dont read reply from cache
        http->request->flags.cachable = false; // dont store reply into cache
    }
    http->doCallouts();
}