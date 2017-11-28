static void
constructHelperQuery(const char *name, helper *hlp, HLPCB *replyHandler, ClientHttpRequest * http, HLPCB *handler, void *data)
{
    ConnStateData * conn = http->getConn();
    const char *fqdn;
    char buf[MAX_REDIRECTOR_REQUEST_STRLEN];
    int sz;
    Http::StatusCode status;
    char claddr[MAX_IPSTRLEN];
    char myaddr[MAX_IPSTRLEN];

    /** TODO: create a standalone method to initialize
     * the cbdata\redirectStateData for all the helpers.
     */
    redirectStateData *r = cbdataAlloc(redirectStateData);
    r->orig_url = xstrdup(http->uri);
    if (conn != NULL)
        r->client_addr = conn->log_addr;
    else
        r->client_addr.setNoAddr();
    r->client_ident = NULL;
#if USE_AUTH
    if (http->request->auth_user_request != NULL) {
        r->client_ident = http->request->auth_user_request->username();
        debugs(61, 5, HERE << "auth-user=" << (r->client_ident?r->client_ident:"NULL"));
    }
#endif

    // HttpRequest initializes with null_string. So we must check both defined() and size()
    if (!r->client_ident && http->request->extacl_user.defined() && http->request->extacl_user.size()) {
        r->client_ident = http->request->extacl_user.termedBuf();
        debugs(61, 5, HERE << "acl-user=" << (r->client_ident?r->client_ident:"NULL"));
    }

    if (!r->client_ident && conn != NULL && conn->clientConnection != NULL && conn->clientConnection->rfc931[0]) {
        r->client_ident = conn->clientConnection->rfc931;
        debugs(61, 5, HERE << "ident-user=" << (r->client_ident?r->client_ident:"NULL"));
    }

#if USE_SSL

    if (!r->client_ident && conn != NULL && Comm::IsConnOpen(conn->clientConnection)) {
        r->client_ident = sslGetUserEmail(fd_table[conn->clientConnection->fd].ssl);
        debugs(61, 5, HERE << "ssl-user=" << (r->client_ident?r->client_ident:"NULL"));
    }
#endif

    if (!r->client_ident)
        r->client_ident = dash_str;

    r->method_s = RequestMethodStr(http->request->method);

    r->handler = handler;

    r->data = cbdataReference(data);

    if ((fqdn = fqdncache_gethostbyaddr(r->client_addr, 0)) == NULL)
        fqdn = dash_str;

    sz = snprintf(buf, MAX_REDIRECTOR_REQUEST_STRLEN, "%s %s/%s %s %s myip=%s myport=%d\n",
                  r->orig_url,
                  r->client_addr.toStr(claddr,MAX_IPSTRLEN),
                  fqdn,
                  r->client_ident[0] ? rfc1738_escape(r->client_ident) : dash_str,
                  r->method_s,
                  http->request->my_addr.toStr(myaddr,MAX_IPSTRLEN),
                  http->request->my_addr.port());

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