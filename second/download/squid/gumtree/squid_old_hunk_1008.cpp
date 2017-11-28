            bodyLength > Config.maxRequestBodySize)
        return 1;       /* too large */

    return 0;
}

// careful: the "current" context may be gone if we wrote an early response
ClientSocketContext::Pointer
ConnStateData::getCurrentContext() const
{
    return currentobject;
}

void
ClientSocketContext::deferRecipientForLater(clientStreamNode * node, HttpReply * rep, StoreIOBuffer receivedData)
{
    debugs(33, 2, "clientSocketRecipient: Deferring request " << http->uri);
    assert(flags.deferred == 0);
    flags.deferred = 1;
    deferredparams.node = node;
    deferredparams.rep = rep;
    deferredparams.queuedBuffer = receivedData;
    return;
}

bool
ClientSocketContext::startOfOutput() const
{
    return http->out.size == 0;
}

size_t
ClientSocketContext::lengthToSend(Range<int64_t> const &available)
{
    /*the size of available range can always fit in a size_t type*/
    size_t maximum = (size_t)available.size();

    if (!http->request->range)
        return maximum;

    assert (canPackMoreRanges());

    if (http->range_iter.debt() == -1)
        return maximum;

    assert (http->range_iter.debt() > 0);

    /* TODO this + the last line could be a range intersection calculation */
    if (available.start < http->range_iter.currentSpec()->offset)
        return 0;

    return min(http->range_iter.debt(), (int64_t)maximum);
}

void
ClientSocketContext::noteSentBodyBytes(size_t bytes)
{
    debugs(33, 7, bytes << " body bytes");

    http->out.offset += bytes;

    if (!http->request->range)
        return;

    if (http->range_iter.debt() != -1) {
        http->range_iter.debt(http->range_iter.debt() - bytes);
        assert (http->range_iter.debt() >= 0);
    }

    /* debt() always stops at -1, below that is a bug */
    assert (http->range_iter.debt() >= -1);
}

bool
ClientHttpRequest::multipartRangeRequest() const
{
    return request->multipartRangeRequest();
}

bool
ClientSocketContext::multipartRangeRequest() const
{
    return http->multipartRangeRequest();
}

void
ClientSocketContext::sendBody(HttpReply * rep, StoreIOBuffer bodyData)
{
    assert(rep == NULL);

    if (!multipartRangeRequest() && !http->request->flags.chunkedReply) {
        size_t length = lengthToSend(bodyData.range());
        noteSentBodyBytes (length);
        AsyncCall::Pointer call = commCbCall(33, 5, "clientWriteBodyComplete",
                                             CommIoCbPtrFun(clientWriteBodyComplete, this));
        Comm::Write(clientConnection, bodyData.data, length, call, NULL);
        return;
    }

    MemBuf mb;
    mb.init();
    if (multipartRangeRequest())
        packRange(bodyData, &mb);
    else
        packChunk(bodyData, mb);

    if (mb.contentSize()) {
        /* write */
        AsyncCall::Pointer call = commCbCall(33, 5, "clientWriteComplete",
                                             CommIoCbPtrFun(clientWriteComplete, this));
        Comm::Write(clientConnection, &mb, call);
    }  else
        writeComplete(clientConnection, NULL, 0, Comm::OK);
}

/**
 * Packs bodyData into mb using chunked encoding. Packs the last-chunk
 * if bodyData is empty.
 */
void
ClientSocketContext::packChunk(const StoreIOBuffer &bodyData, MemBuf &mb)
{
    const uint64_t length =
        static_cast<uint64_t>(lengthToSend(bodyData.range()));
    noteSentBodyBytes(length);

    mb.Printf("%" PRIX64 "\r\n", length);
    mb.append(bodyData.data, length);
    mb.Printf("\r\n");
}

/** put terminating boundary for multiparts */
static void
clientPackTermBound(String boundary, MemBuf * mb)
{
    mb->Printf("\r\n--" SQUIDSTRINGPH "--\r\n", SQUIDSTRINGPRINT(boundary));
    debugs(33, 6, "clientPackTermBound: buf offset: " << mb->size);
}

/** appends a "part" HTTP header (as in a multi-part/range reply) to the buffer */
static void
clientPackRangeHdr(const HttpReply * rep, const HttpHdrRangeSpec * spec, String boundary, MemBuf * mb)
{
    HttpHeader hdr(hoReply);
    Packer p;
    assert(rep);
    assert(spec);

    /* put boundary */
    debugs(33, 5, "clientPackRangeHdr: appending boundary: " << boundary);
    /* rfc2046 requires to _prepend_ boundary with <crlf>! */
    mb->Printf("\r\n--" SQUIDSTRINGPH "\r\n", SQUIDSTRINGPRINT(boundary));

    /* stuff the header with required entries and pack it */

    if (rep->header.has(HDR_CONTENT_TYPE))
        hdr.putStr(HDR_CONTENT_TYPE, rep->header.getStr(HDR_CONTENT_TYPE));

    httpHeaderAddContRange(&hdr, *spec, rep->content_length);

    packerToMemInit(&p, mb);

    hdr.packInto(&p);

    packerClean(&p);

    hdr.clean();

    /* append <crlf> (we packed a header, not a reply) */
    mb->Printf("\r\n");
}

/**
 * extracts a "range" from *buf and appends them to mb, updating
 * all offsets and such.
 */
void
ClientSocketContext::packRange(StoreIOBuffer const &source, MemBuf * mb)
{
    HttpHdrRangeIter * i = &http->range_iter;
    Range<int64_t> available (source.range());
    char const *buf = source.data;

    while (i->currentSpec() && available.size()) {
        const size_t copy_sz = lengthToSend(available);

        if (copy_sz) {
            /*
             * intersection of "have" and "need" ranges must not be empty
             */
            assert(http->out.offset < i->currentSpec()->offset + i->currentSpec()->length);
            assert(http->out.offset + (int64_t)available.size() > i->currentSpec()->offset);

            /*
             * put boundary and headers at the beginning of a range in a
             * multi-range
             */

            if (http->multipartRangeRequest() && i->debt() == i->currentSpec()->length) {
                assert(http->memObject());
                clientPackRangeHdr(
                    http->memObject()->getReply(),  /* original reply */
                    i->currentSpec(),       /* current range */
                    i->boundary,    /* boundary, the same for all */
                    mb);
            }

            /*
             * append content
             */
            debugs(33, 3, "clientPackRange: appending " << copy_sz << " bytes");

            noteSentBodyBytes (copy_sz);

            mb->append(buf, copy_sz);

            /*
             * update offsets
             */
            available.start += copy_sz;

            buf += copy_sz;

        }

        if (!canPackMoreRanges()) {
            debugs(33, 3, "clientPackRange: Returning because !canPackMoreRanges.");

            if (i->debt() == 0)
                /* put terminating boundary for multiparts */
                clientPackTermBound(i->boundary, mb);

            return;
        }

        int64_t nextOffset = getNextRangeOffset();

        assert (nextOffset >= http->out.offset);

        int64_t skip = nextOffset - http->out.offset;

        /* adjust for not to be transmitted bytes */
        http->out.offset = nextOffset;

        if (available.size() <= (uint64_t)skip)
            return;

        available.start += skip;

        buf += skip;

        if (copy_sz == 0)
            return;
    }
}

/** returns expected content length for multi-range replies
 * note: assumes that httpHdrRangeCanonize has already been called
 * warning: assumes that HTTP headers for individual ranges at the
 *          time of the actuall assembly will be exactly the same as
