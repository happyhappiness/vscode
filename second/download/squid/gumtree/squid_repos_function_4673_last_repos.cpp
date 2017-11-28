void
Http::One::Server::processParsedRequest(Http::StreamPointer &context)
{
    if (!buildHttpRequest(context))
        return;

    ClientHttpRequest *http = context->http;
    HttpRequest::Pointer request = http->request;

    if (request->header.has(Http::HdrType::EXPECT)) {
        const String expect = request->header.getList(Http::HdrType::EXPECT);
        const bool supportedExpect = (expect.caseCmp("100-continue") == 0);
        if (!supportedExpect) {
            clientStreamNode *node = context->getClientReplyContext();
            quitAfterError(request.getRaw());
            // setLogUri should called before repContext->setReplyToError
            setLogUri(http, urlCanonicalClean(request.getRaw()));
            clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
            assert (repContext);
            repContext->setReplyToError(ERR_INVALID_REQ, Http::scExpectationFailed, request->method, http->uri,
                                        clientConnection->remote, request.getRaw(), NULL, NULL);
            assert(context->http->out.offset == 0);
            context->pullData();
            clientProcessRequestFinished(this, request);
            return;
        }

        if (Config.accessList.forceRequestBodyContinuation) {
            ACLFilledChecklist bodyContinuationCheck(Config.accessList.forceRequestBodyContinuation, request.getRaw(), NULL);
            if (bodyContinuationCheck.fastCheck().allowed()) {
                debugs(33, 5, "Body Continuation forced");
                request->forcedBodyContinuation = true;
                //sendControlMsg
                HttpReply::Pointer rep = new HttpReply;
                rep->sline.set(Http::ProtocolVersion(), Http::scContinue);

                typedef UnaryMemFunT<Http1::Server, Http::StreamPointer> CbDialer;
                const AsyncCall::Pointer cb = asyncCall(11, 3,  "Http1::Server::proceedAfterBodyContinuation", CbDialer(this, &Http1::Server::proceedAfterBodyContinuation, Http::StreamPointer(context)));
                sendControlMsg(HttpControlMsg(rep, cb));
                return;
            }
        }
    }
    clientProcessRequest(this, parser_, context.getRaw());
}