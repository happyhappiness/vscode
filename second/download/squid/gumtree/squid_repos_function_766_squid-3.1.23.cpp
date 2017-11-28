void
ClientHttpRequest::doCallouts()
{
    assert(calloutContext);

    /*Save the original request for logging purposes*/
    if (!calloutContext->http->al.request)
        calloutContext->http->al.request = HTTPMSGLOCK(request);

    if (!calloutContext->http_access_done) {
        debugs(83, 3, HERE << "Doing calloutContext->clientAccessCheck()");
        calloutContext->http_access_done = true;
        calloutContext->clientAccessCheck();
        return;
    }

#if USE_ADAPTATION
    if (!calloutContext->adaptation_acl_check_done) {
        calloutContext->adaptation_acl_check_done = true;
        if (Adaptation::AccessCheck::Start(
                    Adaptation::methodReqmod, Adaptation::pointPreCache,
                    request, NULL, adaptationAclCheckDoneWrapper, calloutContext))
            return; // will call callback
    }
#endif

    if (!calloutContext->redirect_done) {
        calloutContext->redirect_done = true;
        assert(calloutContext->redirect_state == REDIRECT_NONE);

        if (Config.Program.redirect) {
            debugs(83, 3, HERE << "Doing calloutContext->clientRedirectStart()");
            calloutContext->redirect_state = REDIRECT_PENDING;
            calloutContext->clientRedirectStart();
            return;
        }
    }

    if (!calloutContext->adapted_http_access_done) {
        debugs(83, 3, HERE << "Doing calloutContext->clientAccessCheck2()");
        calloutContext->adapted_http_access_done = true;
        calloutContext->clientAccessCheck2();
        return;
    }

    if (!calloutContext->interpreted_req_hdrs) {
        debugs(83, 3, HERE << "Doing clientInterpretRequestHeaders()");
        calloutContext->interpreted_req_hdrs = 1;
        clientInterpretRequestHeaders(this);
    }

    if (!calloutContext->no_cache_done) {
        calloutContext->no_cache_done = true;

        if (Config.accessList.noCache && request->flags.cachable) {
            debugs(83, 3, HERE << "Doing calloutContext->checkNoCache()");
            calloutContext->checkNoCache();
            return;
        }
    }

    if (!calloutContext->clientside_tos_done) {
        calloutContext->clientside_tos_done = true;
        if (getConn() != NULL) {
            ACLFilledChecklist ch(NULL, request, NULL);
            ch.src_addr = request->client_addr;
            ch.my_addr = request->my_addr;
            int tos = aclMapTOS(Config.accessList.clientside_tos, &ch);
            if (tos)
                comm_set_tos(getConn()->fd, tos);
        }
    }

#if USE_SSL
    if (!calloutContext->sslBumpCheckDone) {
        calloutContext->sslBumpCheckDone = true;
        if (calloutContext->sslBumpAccessCheck())
            return;
        /* else no ssl bump required*/
    }
#endif

    cbdataReferenceDone(calloutContext->http);
    delete calloutContext;
    calloutContext = NULL;
#if HEADERS_LOG

    headersLog(0, 1, request->method, request);
#endif

    debugs(83, 3, HERE << "calling processRequest()");
    processRequest();

#if ICAP_CLIENT
    Adaptation::Icap::History::Pointer ih = request->icapHistory();
    if (ih != NULL)
        ih->logType = logType;
#endif
}