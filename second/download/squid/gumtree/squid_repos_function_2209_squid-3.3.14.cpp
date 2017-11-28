void
ServerStateData::adaptVirginReplyBody(const char *data, ssize_t len)
{
    assert(startedAdaptation);

    if (!virginBodyDestination) {
        debugs(11,3, HERE << "ICAP does not want more virgin body");
        return;
    }

    // grow overflow area if already overflowed
    if (responseBodyBuffer) {
        responseBodyBuffer->append(data, len);
        data = responseBodyBuffer->content();
        len = responseBodyBuffer->contentSize();
    }

    const ssize_t putSize = virginBodyDestination->putMoreData(data, len);
    data += putSize;
    len -= putSize;

    // if we had overflow area, shrink it as necessary
    if (responseBodyBuffer) {
        if (putSize == responseBodyBuffer->contentSize()) {
            delete responseBodyBuffer;
            responseBodyBuffer = NULL;
        } else {
            responseBodyBuffer->consume(putSize);
        }
        return;
    }

    // if we did not have an overflow area, create it as needed
    if (len > 0) {
        assert(!responseBodyBuffer);
        responseBodyBuffer = new MemBuf;
        responseBodyBuffer->init(4096, SQUID_TCP_SO_RCVBUF * 10);
        responseBodyBuffer->append(data, len);
    }
}