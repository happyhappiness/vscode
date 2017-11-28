void
ClientSocketContext::sendBody(HttpReply * rep, StoreIOBuffer bodyData)
{
    assert(rep == NULL);

    if (!multipartRangeRequest()) {
        size_t length = lengthToSend(bodyData.range());
        noteSentBodyBytes (length);
        AsyncCall::Pointer call = commCbCall(33, 5, "clientWriteBodyComplete",
                                             CommIoCbPtrFun(clientWriteBodyComplete, this));
        comm_write(fd(), bodyData.data, length, call );
        return;
    }

    MemBuf mb;
    mb.init();
    packRange(bodyData, &mb);

    if (mb.contentSize()) {
        /* write */
        AsyncCall::Pointer call = commCbCall(33, 5, "clientWriteComplete",
                                             CommIoCbPtrFun(clientWriteComplete, this));
        comm_write_mbuf(fd(), &mb, call);
    }  else
        writeComplete(fd(), NULL, 0, COMM_OK);
}