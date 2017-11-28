void
Ident::ConnectDone(const Comm::ConnectionPointer &conn, comm_err_t status, int xerrno, void *data)
{
    IdentStateData *state = (IdentStateData *)data;

    if (status != COMM_OK) {
        if (status == COMM_TIMEOUT) {
            debugs(30, 3, "IDENT connection timeout to " << state->conn->remote);
        }
        return;
    }

    assert(conn != NULL && conn == state->conn);

    /*
     * see if any of our clients still care
     */
    IdentClient *c;
    for (c = state->clients; c; c = c->next) {
        if (cbdataReferenceValid(c->callback_data))
            break;
    }

    if (c == NULL) {
        /* no clients care */
        conn->close();
        return;
    }

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