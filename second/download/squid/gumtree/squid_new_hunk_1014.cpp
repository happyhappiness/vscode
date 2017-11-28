    }

    return false;
}
#endif // USE_OPENSSL

/**
 * Check on_unsupported_protocol checklist and return true if tunnel mode selected
 * or false otherwise
 */
bool
clientTunnelOnError(ConnStateData *conn, Http::StreamPointer &context, HttpRequest::Pointer &request, const HttpRequestMethod& method, err_type requestError)
{
    if (conn->mayTunnelUnsupportedProto()) {
        ACLFilledChecklist checklist(Config.accessList.on_unsupported_protocol, request.getRaw(), nullptr);
        checklist.requestErrorType = requestError;
        checklist.src_addr = conn->clientConnection->remote;
        checklist.my_addr = conn->clientConnection->local;
        checklist.conn(conn);
        allow_t answer = checklist.fastCheck();
        if (answer == ACCESS_ALLOWED && answer.kind == 1) {
            debugs(33, 3, "Request will be tunneled to server");
            if (context) {
                assert(conn->pipeline.front() == context); // XXX: still assumes HTTP/1 semantics
                context->finished(); // Will remove from conn->pipeline queue
            }
            Comm::SetSelect(conn->clientConnection->fd, COMM_SELECT_READ, NULL, NULL, 0);
            return conn->initiateTunneledRequest(request, Http::METHOD_NONE, "unknown-protocol", conn->preservedClientData);
        } else {
            debugs(33, 3, "Continue with returning the error: " << requestError);
        }
    }

    return false;
}

void
clientProcessRequestFinished(ConnStateData *conn, const HttpRequest::Pointer &request)
{
    /*
     * DPW 2007-05-18
     * Moved the TCP_RESET feature from clientReplyContext::sendMoreData
     * to here because calling comm_reset_close() causes http to
     * be freed before accessing.
     */
    if (request != NULL && request->flags.resetTcp && Comm::IsConnOpen(conn->clientConnection)) {
        debugs(33, 3, HERE << "Sending TCP RST on " << conn->clientConnection);
        conn->flags.readMore = false;
        comm_reset_close(conn->clientConnection);
    }
}

void
clientProcessRequest(ConnStateData *conn, const Http1::RequestParserPointer &hp, Http::Stream *context)
{
    ClientHttpRequest *http = context->http;
    bool chunked = false;
    bool mustReplyToOptions = false;
    bool unsupportedTe = false;
    bool expectBody = false;

    // We already have the request parsed and checked, so we
    // only need to go through the final body/conn setup to doCallouts().
    assert(http->request);
    HttpRequest::Pointer request = http->request;

    // temporary hack to avoid splitting this huge function with sensitive code
    const bool isFtp = !hp;

    // Some blobs below are still HTTP-specific, but we would have to rewrite
    // this entire function to remove them from the FTP code path. Connection
    // setup and body_pipe preparation blobs are needed for FTP.

    request->clientConnectionManager = conn;
