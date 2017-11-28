void
ClientHttpRequest::doCallouts()
{
    assert(calloutContext);

    /*Save the original request for logging purposes*/
    if (!calloutContext->http->al->request) {
        calloutContext->http->al->request = request;
        HTTPMSGLOCK(calloutContext->http->al->request);
    }

    if (!calloutContext->error) {
        // CVE-2009-0801: verify the Host: header is consistent with other known details.
        if (!calloutContext->host_header_verify_done) {
            debugs(83, 3, HERE << "Doing calloutContext->hostHeaderVerify()");
            calloutContext->host_header_verify_done = true;
            calloutContext->hostHeaderVerify();
            return;
        }

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
                        request, NULL, this))
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

        if (!calloutContext->store_id_done) {
            calloutContext->store_id_done = true;
            assert(calloutContext->store_id_state == REDIRECT_NONE);

            if (Config.Program.store_id) {
                debugs(83, 3,"Doing calloutContext->clientStoreIdStart()");
                calloutContext->store_id_state = REDIRECT_PENDING;
                calloutContext->clientStoreIdStart();
                return;
            }
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
    } //  if !calloutContext->error

    if (!calloutContext->tosToClientDone) {
        calloutContext->tosToClientDone = true;
        if (getConn() != NULL && Comm::IsConnOpen(getConn()->clientConnection)) {
            ACLFilledChecklist ch(NULL, request, NULL);
            ch.src_addr = request->client_addr;
            ch.my_addr = request->my_addr;
            tos_t tos = aclMapTOS(Ip::Qos::TheConfig.tosToClient, &ch);
            if (tos)
                Ip::Qos::setSockTos(getConn()->clientConnection, tos);
        }
    }

    if (!calloutContext->nfmarkToClientDone) {
        calloutContext->nfmarkToClientDone = true;
        if (getConn() != NULL && Comm::IsConnOpen(getConn()->clientConnection)) {
            ACLFilledChecklist ch(NULL, request, NULL);
            ch.src_addr = request->client_addr;
            ch.my_addr = request->my_addr;
            nfmark_t mark = aclMapNfmark(Ip::Qos::TheConfig.nfmarkToClient, &ch);
            if (mark)
                Ip::Qos::setSockNfmark(getConn()->clientConnection, mark);
        }
    }

#if USE_SSL
    // We need to check for SslBump even if the calloutContext->error is set
    // because bumping may require delaying the error until after CONNECT.
    if (!calloutContext->sslBumpCheckDone) {
        calloutContext->sslBumpCheckDone = true;
        if (calloutContext->sslBumpAccessCheck())
            return;
        /* else no ssl bump required*/
    }
#endif

    if (calloutContext->error) {
        const char *storeUri = request->storeId();
        StoreEntry *e= storeCreateEntry(storeUri, storeUri, request->flags, request->method);
#if USE_SSL
        if (sslBumpNeeded()) {
            // set final error but delay sending until we bump
            Ssl::ServerBump *srvBump = new Ssl::ServerBump(request, e);
            errorAppendEntry(e, calloutContext->error);
            calloutContext->error = NULL;
            getConn()->setServerBump(srvBump);
            e->unlock();
        } else
#endif
        {
            // send the error to the client now
            clientStreamNode *node = (clientStreamNode *)client_stream.tail->prev->data;
            clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
            assert (repContext);
            repContext->setReplyToStoreEntry(e, "immediate SslBump error");
            errorAppendEntry(e, calloutContext->error);
            calloutContext->error = NULL;
            if (calloutContext->readNextRequest)
                getConn()->flags.readMore = true; // resume any pipeline reads.
            node = (clientStreamNode *)client_stream.tail->data;
            clientStreamRead(node, this, node->readBuffer);
            e->unlock();
            return;
        }
    }

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