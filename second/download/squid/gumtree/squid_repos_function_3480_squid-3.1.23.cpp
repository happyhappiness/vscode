int
connKeepReadingIncompleteRequest(ConnStateData * conn)
{
    // when we read chunked requests, the entire body is buffered
    // XXX: this check ignores header size and its limits.
    if (conn->in.dechunkingState == ConnStateData::chunkParsing)
        return ((int64_t)conn->in.notYetUsed) < Config.maxChunkedRequestBodySize;

    return conn->in.notYetUsed >= Config.maxRequestHeaderSize ? 0 : 1;
}