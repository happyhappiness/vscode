ClientRequestContext::clientAccessCheck2()
{
    if (Config.accessList.adapted_http) {
        acl_checklist = clientAclChecklistCreate(Config.accessList.adapted_http, http);
        acl_checklist->nonBlockingCheck(clientAccessCheckDoneWrapper, this);
    } else {
        debugs(85, 2, HERE << "No adapted_http_access configuration. default: ALLOW");
        clientAccessCheckDone(ACCESS_ALLOWED);
    }
}

void
clientAccessCheckDoneWrapper(allow_t answer, void *data)
{
    ClientRequestContext *calloutContext = (ClientRequestContext *) data;

    if (!calloutContext->httpStateIsValid())
        return;

    calloutContext->clientAccessCheckDone(answer);
}

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
        /* Send an error */
        int require_auth = (answer == ACCESS_REQ_PROXY_AUTH || aclIsProxyAuth(AclMatchedName));
        debugs(85, 5, "Access Denied: " << http->uri);
        debugs(85, 5, "AclMatchedName = " << (AclMatchedName ? AclMatchedName : "<null>"));
#if USE_AUTH
        if (require_auth)
            debugs(33, 5, "Proxy Auth Message = " << (proxy_auth_msg ? proxy_auth_msg : "<null>"));
#endif

        /*
         * NOTE: get page_id here, based on AclMatchedName because if
         * USE_DELAY_POOLS is enabled, then AclMatchedName gets clobbered in
         * the clientCreateStoreEntry() call just below.  Pedro Ribeiro
         * <pribeiro@isel.pt>
         */
        page_id = aclGetDenyInfoPage(&Config.denyInfoList, AclMatchedName, answer != ACCESS_REQ_PROXY_AUTH);

        http->logType = LOG_TCP_DENIED;

        if (require_auth) {
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

        clientStreamNode *node = (clientStreamNode *)http->client_stream.tail->prev->data;
        clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
        assert (repContext);
        Ip::Address tmpnoaddr;
        tmpnoaddr.SetNoAddr();
        repContext->setReplyToError(page_id, status,
                                    http->request->method, NULL,
                                    http->getConn() != NULL ? http->getConn()->clientConnection->remote : tmpnoaddr,
                                    http->request,
                                    NULL,
#if USE_AUTH
                                    http->getConn() != NULL && http->getConn()->auth_user_request != NULL ?
                                    http->getConn()->auth_user_request : http->request->auth_user_request);
#else
                                    NULL);
#endif
        http->getConn()->flags.readMore = true; // resume any pipeline reads.
        node = (clientStreamNode *)http->client_stream.tail->data;
        clientStreamRead(node, http, node->readBuffer);
        return;
    }

    /* ACCESS_ALLOWED continues here ... */
