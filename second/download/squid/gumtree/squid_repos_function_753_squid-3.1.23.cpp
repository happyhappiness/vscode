bool
ClientRequestContext::sslBumpAccessCheck()
{
    if (http->request->method == METHOD_CONNECT &&
            Config.accessList.ssl_bump && http->getConn()->port->sslBump) {
        debugs(85, 5, HERE << "SslBump possible, checking ACL");

        ACLFilledChecklist *acl_checklist = clientAclChecklistCreate(Config.accessList.ssl_bump, http);
        acl_checklist->nonBlockingCheck(sslBumpAccessCheckDoneWrapper, this);
        return true;
    } else {
        http->sslBumpNeeded(false);
        return false;
    }
}