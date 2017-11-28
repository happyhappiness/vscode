void
redirectStart(ClientHttpRequest * http, RH * handler, void *data)
{
    ConnStateData * conn = http->getConn();
    redirectStateData *r = NULL;
    const char *fqdn;
    char buf[MAX_REDIRECTOR_REQUEST_STRLEN];
    int sz;
    http_status status;
    char claddr[MAX_IPSTRLEN];
    char myaddr[MAX_IPSTRLEN];
    assert(http);
    assert(handler);
    debugs(61, 5, "redirectStart: '" << http->uri << "'");

    if (Config.onoff.redirector_bypass && redirectors->stats.queue_size) {
        /* Skip redirector if there is one request queued */
        n_bypassed++;
        handler(data, NULL);
        return;
    }

    r = cbdataAlloc(redirectStateData);
    r->orig_url = xstrdup(http->uri);
    if (conn != NULL)
        r->client_addr = conn->log_addr;
    else
        r->client_addr.SetNoAddr();
    r->client_ident = NULL;
    if (http->request->auth_user_request != NULL) {
        r->client_ident = http->request->auth_user_request->username();
        debugs(61, 5, HERE << "auth-user=" << (r->client_ident?r->client_ident:"NULL"));
    }

    // HttpRequest initializes with null_string. So we must check both defined() and size()
    if (!r->client_ident && http->request->extacl_user.defined() && http->request->extacl_user.size()) {
        r->client_ident = http->request->extacl_user.termedBuf();
        debugs(61, 5, HERE << "acl-user=" << (r->client_ident?r->client_ident:"NULL"));
    }

    if (!r->client_ident && (conn != NULL && conn->rfc931[0])) {
        r->client_ident = conn->rfc931;
        debugs(61, 5, HERE << "ident-user=" << (r->client_ident?r->client_ident:"NULL"));
    }

#if USE_SSL

    if (!r->client_ident && conn != NULL) {
        r->client_ident = sslGetUserEmail(fd_table[conn->fd].ssl);
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
                  r->client_addr.NtoA(claddr,MAX_IPSTRLEN),
                  fqdn,
                  r->client_ident[0] ? rfc1738_escape(r->client_ident) : dash_str,
                  r->method_s,
                  http->request->my_addr.NtoA(myaddr,MAX_IPSTRLEN),
                  http->request->my_addr.GetPort());

    if ((sz<=0) || (sz>=MAX_REDIRECTOR_REQUEST_STRLEN)) {
        if (sz<=0) {
            status = HTTP_INTERNAL_SERVER_ERROR;
            debugs(61, DBG_CRITICAL, "ERROR: Gateway Failure. Can not build request to be passed to redirector. Request ABORTED.");
        } else {
            status = HTTP_REQUEST_URI_TOO_LARGE;
            debugs(61, DBG_CRITICAL, "ERROR: Gateway Failure. Request passed to redirector exceeds MAX_REDIRECTOR_REQUEST_STRLEN (" << MAX_REDIRECTOR_REQUEST_STRLEN << "). Request ABORTED.");
        }

        clientStreamNode *node = (clientStreamNode *)http->client_stream.tail->prev->data;
        clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
        assert (repContext);
        IpAddress tmpnoaddr;
        tmpnoaddr.SetNoAddr();
        repContext->setReplyToError(ERR_GATEWAY_FAILURE, status,
                                    http->request->method, NULL,
                                    http->getConn() != NULL ? http->getConn()->peer : tmpnoaddr,
                                    http->request,
                                    NULL,
                                    http->getConn() != NULL && http->getConn()->auth_user_request != NULL ?
                                    http->getConn()->auth_user_request : http->request->auth_user_request);

        node = (clientStreamNode *)http->client_stream.tail->data;
        clientStreamRead(node, http, node->readBuffer);
        return;
    }

    debugs(61,6, HERE << "sending '" << buf << "' to the helper");
    helperSubmit(redirectors, buf, redirectHandleReply, r);
}