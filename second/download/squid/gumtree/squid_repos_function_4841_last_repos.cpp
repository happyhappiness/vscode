void
Http::Stream::sendBody(StoreIOBuffer bodyData)
{
    if (!multipartRangeRequest() && !http->request->flags.chunkedReply) {
        size_t length = lengthToSend(bodyData.range());
        noteSentBodyBytes(length);
        getConn()->write(bodyData.data, length);
        return;
    }

    MemBuf mb;
    mb.init();
    if (multipartRangeRequest())
        packRange(bodyData, &mb);
    else
        packChunk(bodyData, mb);

    if (mb.contentSize())
        getConn()->write(&mb);
    else
        writeComplete(0);
}