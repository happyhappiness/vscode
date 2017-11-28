void
Ident::ConnectDone(const Comm::ConnectionPointer &conn, Comm::Flag status, int, void *data)
{
    IdentStateData *state = (IdentStateData *)data;

    if (status != Comm::OK) {
        if (status == Comm::TIMEOUT)
            debugs(30, 3, "IDENT connection timeout to " << state->conn->remote);
        state->deleteThis(status == Comm::TIMEOUT ? "connect timeout" : "connect error");
        return;
    }

    /*
     * see if any of our clients still care
     */
    IdentClient *c;
    for (c = state->clients; c; c = c->next) {
        if (cbdataReferenceValid(c->callback_data))
            break;
    }

    if (c == NULL) {
        state->deleteThis("client(s) aborted");
        return;
    }

    assert(conn != NULL && conn == state->conn);
    comm_add_close_handler(conn->fd, Ident::Close, state);

    AsyncCall::Pointer writeCall = commCbCall(5,4, "Ident::WriteFeedback",
                                   CommIoCbPtrFun(Ident::WriteFeedback, state));
    Comm::Write(conn, &state->queryMsg, writeCall);
    AsyncCall::Pointer readCall = commCbCall(5,4, "Ident::ReadReply",
                                  CommIoCbPtrFun(Ident::ReadReply, state));
    comm_read(conn, state->buf, IDENT_BUFSIZE, readCall);
    AsyncCall::Pointer timeoutCall = commCbCall(5,4, "Ident::Timeout",
                                     CommTimeoutCbPtrFun(Ident::Timeout, state));
    commSetConnTimeout(conn, Ident::TheConfig.timeout, timeoutCall);
}