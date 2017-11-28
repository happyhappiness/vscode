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

        /* Send an auth challenge or error */
        // XXX: do we still need aclIsProxyAuth() ?
        bool auth_challenge = (answer == ACCESS_AUTH_REQUIRED || aclIsProxyAuth(AclMatchedName));
        debugs(85, 5, "Access Denied: " << http->uri);
        debugs(85, 5, "AclMatchedName = " << (AclMatchedName ? AclMatchedName : "<null>"));
#if USE_AUTH
        if (auth_challenge)
            debugs(33, 5, "Proxy Auth Message = " << (proxy_auth_msg ? proxy_auth_msg : "<null>"));
#endif

        /*
         * NOTE: get page_id here, based on AclMatchedName because if
         * USE_DELAY_POOLS is enabled, then AclMatchedName gets clobbered in
         * the clientCreateStoreEntry() call just below.  Pedro Ribeiro
         * <pribeiro@isel.pt>
         */
        page_id = aclGetDenyInfoPage(&Config.denyInfoList, AclMatchedName, answer != ACCESS_AUTH_REQUIRED);

        http->logType = LOG_TCP_DENIED;

        if (auth_challenge) {
#if USE_AUTH
            if (http->request->flags.sslBumped) {
                /*SSL Bumped request, authentication is not possible*/
                status = Http::scForbidden;
            } else if (!http->flags.accel) {
                /* Proxy authorisation needed */
                status = Http::scProxyAuthenticationRequired;
            } else {
                /* WWW authorisation needed */
                status = Http::scUnauthorized;
            }
#else
            // need auth, but not possible to do.
            status = Http::scForbidden;
#endif
            if (page_id == ERR_NONE)
                page_id = ERR_CACHE_ACCESS_DENIED;
        } else {
            status = Http::scForbidden;

            if (page_id == ERR_NONE)
                page_id = ERR_ACCESS_DENIED;
        }

        Ip::Address tmpnoaddr;
        tmpnoaddr.setNoAddr();
        error = clientBuildError(page_id, status,
                                 NULL,
                                 http->getConn() != NULL ? http->getConn()->clientConnection->remote : tmpnoaddr,
                                 http->request
                                );

#if USE_AUTH
        error->auth_user_request =
            http->getConn() != NULL && http->getConn()->getAuth() != NULL ?
            http->getConn()->getAuth() : http->request->auth_user_request;
#endif

        readNextRequest = true;
    }

    /* ACCESS_ALLOWED continues here ... */
    safe_free(http->uri);

    http->uri = xstrdup(urlCanonical(http->request));

    http->doCallouts();
}