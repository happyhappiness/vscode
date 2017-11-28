void
ConnStateData::finishDechunkingRequest(HttpParser *hp)
{
    debugs(33, 5, HERE << "finish dechunking; content: " << in.dechunked.contentSize());

    assert(in.dechunkingState == chunkReady);

    const mb_size_t headerSize = HttpParserRequestLen(hp);

    // dechunking cannot make data bigger
    assert(headerSize + in.dechunked.contentSize() + in.chunked.contentSize()
           <= static_cast<mb_size_t>(in.notYetUsed));
    assert(in.notYetUsed <= in.allocatedSize);

    // copy dechunked content
    char *end = in.buf + headerSize;
    xmemmove(end, in.dechunked.content(), in.dechunked.contentSize());
    end += in.dechunked.contentSize();

    // copy post-chunks leftovers, if any, caused by request pipelining?
    if (in.chunked.contentSize()) {
        xmemmove(end, in.chunked.content(), in.chunked.contentSize());
        end += in.chunked.contentSize();
    }

    in.notYetUsed = end - in.buf;

    cleanDechunkingRequest();
}