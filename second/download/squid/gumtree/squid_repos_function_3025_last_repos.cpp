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
        if (answer.allowed() && answer.kind == 1) {
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