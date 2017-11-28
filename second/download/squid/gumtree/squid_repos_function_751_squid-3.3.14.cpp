void
ClientRequestContext::clientAccessCheckDone(const allow_t &answer)
{
    acl_checklist = NULL;
    err_type page_id;
    http_status status;
    debugs(85, 2, "The request " <<
           RequestMethodStr(http->request->method) << " " <<
           http->uri << " is " << answer <<
           ", because it matched '" <<
           (AclMatchedName ? AclMatchedName : "NO ACL's") << "'" );

#if USE_AUTH
    char const *proxy_auth_msg = "<null>";
    if (http->getConn() != NULL && http->getConn()->auth_user_request != NULL)
        proxy_auth_msg = http->getConn()->auth_user_request->denyMessage("<null>");
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
                status = HTTP_FORBIDDEN;
            } else if (!http->flags.accel) {
                /* Proxy authorisation needed */
                status = HTTP_PROXY_AUTHENTICATION_REQUIRED;
            } else {
                /* WWW authorisation needed */
                status = HTTP_UNAUTHORIZED;
            }
#else
            // need auth, but not possible to do.
            status = HTTP_FORBIDDEN;
#endif
            if (page_id == ERR_NONE)
                page_id = ERR_CACHE_ACCESS_DENIED;
        } else {
            status = HTTP_FORBIDDEN;

            if (page_id == ERR_NONE)
                page_id = ERR_ACCESS_DENIED;
        }

        Ip::Address tmpnoaddr;
        tmpnoaddr.SetNoAddr();
        error = clientBuildError(page_id, status,
                                 NULL,
                                 http->getConn() != NULL ? http->getConn()->clientConnection->remote : tmpnoaddr,
                                 http->request
                                );

#if USE_AUTH
        error->auth_user_request =
            http->getConn() != NULL && http->getConn()->auth_user_request != NULL ?
            http->getConn()->auth_user_request : http->request->auth_user_request;
#endif

        readNextRequest = true;
    }

    /* ACCESS_ALLOWED continues here ... */
    safe_free(http->uri);

    http->uri = xstrdup(urlCanonical(http->request));

    http->doCallouts();
}