void
ServerStateData::sendMoreRequestBody()
{
    assert(requestBodySource != NULL);
    assert(!requestSender);

    const Comm::ConnectionPointer conn = dataConnection();

    if (!Comm::IsConnOpen(conn)) {
        debugs(9,3, HERE << "cannot send request body to closing " << conn);
        return; // wait for the kid's close handler; TODO: assert(closer);
    }

    MemBuf buf;
    if (getMoreRequestBody(buf) && buf.contentSize() > 0) {
        debugs(9,3, HERE << "will write " << buf.contentSize() << " request body bytes");
        typedef CommCbMemFunT<ServerStateData, CommIoCbParams> Dialer;
        requestSender = JobCallback(93,3, Dialer, this, ServerStateData::sentRequestBody);
        Comm::Write(conn, &buf, requestSender);
    } else {
        debugs(9,3, HERE << "will wait for more request body bytes or eof");
        requestSender = NULL;
    }
}