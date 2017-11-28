void
ClientRequestContext::clientRedirectStart()
{
    debugs(33, 5, HERE << "'" << http->uri << "'");
    (void)SyncNotes(*http->al, *http->request);
    if (Config.accessList.redirector) {
        acl_checklist = clientAclChecklistCreate(Config.accessList.redirector, http);
        acl_checklist->nonBlockingCheck(clientRedirectAccessCheckDone, this);
    } else
        redirectStart(http, clientRedirectDoneWrapper, this);
}