static void
constructHelperQuery(const char *name, helper *hlp, HLPCB *replyHandler, ClientHttpRequest * http, HLPCB *handler, void *data, Format::Format *requestExtrasFmt)
{
    char buf[MAX_REDIRECTOR_REQUEST_STRLEN];
    int sz;
    Http::StatusCode status;

    /** TODO: create a standalone method to initialize
     * the RedirectStateData for all the helpers.
     */
    RedirectStateData *r = new RedirectStateData(http->uri);
    r->handler = handler;
    r->data = cbdataReference(data);

    static MemBuf requestExtras;
    requestExtras.reset();
    if (requestExtrasFmt)
        requestExtrasFmt->assemble(requestExtras, http->al, 0);

    sz = snprintf(buf, MAX_REDIRECTOR_REQUEST_STRLEN, "%s%s%s\n",
                  r->orig_url.c_str(),
                  requestExtras.hasContent() ? " " : "",
                  requestExtras.hasContent() ? requestExtras.content() : "");

    if ((sz<=0) || (sz>=MAX_REDIRECTOR_REQUEST_STRLEN)) {
        if (sz<=0) {
            status = Http::scInternalServerError;
            debugs(61, DBG_CRITICAL, "ERROR: Gateway Failure. Can not build request to be passed to " << name << ". Request ABORTED.");
        } else {
            status = Http::scUriTooLong;
            debugs(61, DBG_CRITICAL, "ERROR: Gateway Failure. Request passed to " << name << " exceeds MAX_REDIRECTOR_REQUEST_STRLEN (" << MAX_REDIRECTOR_REQUEST_STRLEN << "). Request ABORTED.");
        }

        clientStreamNode *node = (clientStreamNode *)http->client_stream.tail->prev->data;
        clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
        assert (repContext);
        Ip::Address tmpnoaddr;
        tmpnoaddr.setNoAddr();
        repContext->setReplyToError(ERR_GATEWAY_FAILURE, status,
                                    http->request->method, NULL,
                                    http->getConn() != NULL && http->getConn()->clientConnection != NULL ?
                                    http->getConn()->clientConnection->remote : tmpnoaddr,
                                    http->request,
                                    NULL,
#if USE_AUTH
                                    http->getConn() != NULL && http->getConn()->getAuth() != NULL ?
                                    http->getConn()->getAuth() : http->request->auth_user_request);
#else
                                    NULL);
#endif

        node = (clientStreamNode *)http->client_stream.tail->data;
        clientStreamRead(node, http, node->readBuffer);
        return;
    }