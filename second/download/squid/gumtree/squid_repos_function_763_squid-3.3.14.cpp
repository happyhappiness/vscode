bool
ClientRequestContext::sslBumpAccessCheck()
{
    // If SSL connection tunneling or bumping decision has been made, obey it.
    const Ssl::BumpMode bumpMode = http->getConn()->sslBumpMode;
    if (bumpMode != Ssl::bumpEnd) {
        debugs(85, 5, HERE << "SslBump already decided (" << bumpMode <<
               "), " << "ignoring ssl_bump for " << http->getConn());
        http->al->ssl.bumpMode = bumpMode; // inherited from bumped connection
        return false;
    }

    // If we have not decided yet, decide whether to bump now.

    // Bumping here can only start with a CONNECT request on a bumping port
    // (bumping of intercepted SSL conns is decided before we get 1st request).
    // We also do not bump redirected CONNECT requests.
    if (http->request->method != METHOD_CONNECT || http->redirect.status ||
            !Config.accessList.ssl_bump || !http->getConn()->port->sslBump) {
        http->al->ssl.bumpMode = Ssl::bumpEnd; // SslBump does not apply; log -
        debugs(85, 5, HERE << "cannot SslBump this request");
        return false;
    }

    // Do not bump during authentication: clients would not proxy-authenticate
    // if we delay a 407 response and respond with 200 OK to CONNECT.
    if (error && error->httpStatus == HTTP_PROXY_AUTHENTICATION_REQUIRED) {
        http->al->ssl.bumpMode = Ssl::bumpEnd; // SslBump does not apply; log -
        debugs(85, 5, HERE << "no SslBump during proxy authentication");
        return false;
    }

    debugs(85, 5, HERE << "SslBump possible, checking ACL");

    ACLFilledChecklist *acl_checklist = clientAclChecklistCreate(Config.accessList.ssl_bump, http);
    acl_checklist->nonBlockingCheck(sslBumpAccessCheckDoneWrapper, this);
    return true;
}