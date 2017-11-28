void
ClientRequestContext::hostHeaderVerifyFailed(const char *A, const char *B)
{
    // IP address validation for Host: failed. Admin wants to ignore them.
    // NP: we do not yet handle CONNECT tunnels well, so ignore for them
    if (!Config.onoff.hostStrictVerify && http->request->method != METHOD_CONNECT) {
        debugs(85, 3, "SECURITY ALERT: Host header forgery detected on " << http->getConn()->clientConnection <<
               " (" << A << " does not match " << B << ") on URL: " << urlCanonical(http->request));

        // NP: it is tempting to use 'flags.noCache' but that is all about READing cache data.
        // The problems here are about WRITE for new cache content, which means flags.cachable
        http->request->flags.cachable = 0; // MUST NOT cache (for now)
        // XXX: when we have updated the cache key to base on raw-IP + URI this cacheable limit can go.
        http->request->flags.hierarchical = 0; // MUST NOT pass to peers (for now)
        // XXX: when we have sorted out the best way to relay requests properly to peers this hierarchical limit can go.
        http->doCallouts();
        return;
    }

    debugs(85, DBG_IMPORTANT, "SECURITY ALERT: Host header forgery detected on " <<
           http->getConn()->clientConnection << " (" << A << " does not match " << B << ")");
    debugs(85, DBG_IMPORTANT, "SECURITY ALERT: By user agent: " << http->request->header.getStr(HDR_USER_AGENT));
    debugs(85, DBG_IMPORTANT, "SECURITY ALERT: on URL: " << urlCanonical(http->request));

    // IP address validation for Host: failed. reject the connection.
    clientStreamNode *node = (clientStreamNode *)http->client_stream.tail->prev->data;
    clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
    assert (repContext);
    repContext->setReplyToError(ERR_CONFLICT_HOST, HTTP_CONFLICT,
                                http->request->method, NULL,
                                http->getConn()->clientConnection->remote,
                                http->request,
                                NULL,
#if USE_AUTH
                                http->getConn() != NULL && http->getConn()->auth_user_request != NULL ?
                                http->getConn()->auth_user_request : http->request->auth_user_request);
#else
                                NULL);