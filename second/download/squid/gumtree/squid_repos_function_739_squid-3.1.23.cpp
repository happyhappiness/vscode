void
ClientRequestContext::clientAccessCheck2()
{
    if (Config.accessList.adapted_http) {
        acl_checklist = clientAclChecklistCreate(Config.accessList.adapted_http, http);
        acl_checklist->nonBlockingCheck(clientAccessCheckDoneWrapper, this);
    } else {
        debugs(85, 2, HERE << "No adapted_http_access configuration.");
        clientAccessCheckDone(ACCESS_ALLOWED);
    }
}