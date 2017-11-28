void
ClientRequestContext::clientAccessCheck()
{
#if FOLLOW_X_FORWARDED_FOR
    if (!http->request->flags.done_follow_x_forwarded_for &&
            Config.accessList.followXFF &&
            http->request->header.has(HDR_X_FORWARDED_FOR)) {

        /* we always trust the direct client address for actual use */
        http->request->indirect_client_addr = http->request->client_addr;
        http->request->indirect_client_addr.SetPort(0);

        /* setup the XFF iterator for processing */
        http->request->x_forwarded_for_iterator = http->request->header.getList(HDR_X_FORWARDED_FOR);

        /* begin by checking to see if we trust direct client enough to walk XFF */
        acl_checklist = clientAclChecklistCreate(Config.accessList.followXFF, http);
        acl_checklist->nonBlockingCheck(clientFollowXForwardedForCheck, this);
        return;
    }
#endif /* FOLLOW_X_FORWARDED_FOR */

    if (Config.accessList.http) {
        acl_checklist = clientAclChecklistCreate(Config.accessList.http, http);
        acl_checklist->nonBlockingCheck(clientAccessCheckDoneWrapper, this);
    } else {
        debugs(0, DBG_CRITICAL, "No http_access configuration found. This will block ALL traffic");
        clientAccessCheckDone(ACCESS_DENIED);
    }
}