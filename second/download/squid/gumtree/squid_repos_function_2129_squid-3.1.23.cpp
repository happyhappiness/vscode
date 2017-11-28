void
ServerStateData::sendMoreRequestBody()
{
    assert(requestBodySource != NULL);
    assert(!requestSender);

    const int fd = dataDescriptor();

    if (!canSend(fd)) {
        debugs(9,3, HERE << "cannot send request body to closing FD " << fd);
        return; // wait for the kid's close handler; TODO: assert(closer);
    }

    MemBuf buf;
    if (requestBodySource->getMoreData(buf)) {
        debugs(9,3, HERE << "will write " << buf.contentSize() << " request body bytes");
        typedef CommCbMemFunT<ServerStateData, CommIoCbParams> Dialer;
        requestSender = JobCallback(93,3,
                                    Dialer, this, ServerStateData::sentRequestBody);
        comm_write_mbuf(fd, &buf, requestSender);
    } else {
        debugs(9,3, HERE << "will wait for more request body bytes or eof");
        requestSender = NULL;
    }
}