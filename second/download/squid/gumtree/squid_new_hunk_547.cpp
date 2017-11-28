
void
ClientRequestContext::clientAccessCheckDone(const allow_t &answer)
{
    acl_checklist = NULL;
    err_type page_id;
    Http::StatusCode status;
    debugs(85, 2, "The request " <<
           RequestMethodStr(http->request->method) << " " <<
           http->uri << " is " << answer <<
           "; last ACL checked: " << (AclMatchedName ? AclMatchedName : "[none]"));

#if USE_AUTH
    char const *proxy_auth_msg = "<null>";
    if (http->getConn() != NULL && http->getConn()->getAuth() != NULL)
        proxy_auth_msg = http->getConn()->getAuth()->denyMessage("<null>");
    else if (http->request->auth_user_request != NULL)
        proxy_auth_msg = http->request->auth_user_request->denyMessage("<null>");
#endif

    if (answer != ACCESS_ALLOWED) {
        // auth has a grace period where credentials can be expired but okay not to challenge.
