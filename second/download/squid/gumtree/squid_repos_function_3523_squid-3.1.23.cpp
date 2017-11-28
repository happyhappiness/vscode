bool
ConnStateData::parseRequestChunks(HttpParser *)
{
    debugs(33,5, HERE << "parsing chunked request body at " <<
           in.chunkedSeen << " < " << in.notYetUsed);
    assert(in.bodyParser);
    assert(in.dechunkingState == chunkParsing);

    assert(in.chunkedSeen <= in.notYetUsed);
    const mb_size_t fresh = in.notYetUsed - in.chunkedSeen;

    // be safe: count some chunked coding metadata towards the total body size
    if (fresh + in.dechunked.contentSize() > Config.maxChunkedRequestBodySize) {
        debugs(33,3, HERE << "chunked body (" << fresh << " + " <<
               in.dechunked.contentSize() << " may exceed " <<
               "chunked_request_body_max_size=" <<
               Config.maxChunkedRequestBodySize);
        in.dechunkingState = chunkError;
        return false;
    }

    if (fresh > in.chunked.potentialSpaceSize()) {
        // should not happen if Config.maxChunkedRequestBodySize is reasonable
        debugs(33,1, HERE << "request_body_max_size exceeds chunked buffer " <<
               "size: " << fresh << " + " << in.chunked.contentSize() << " > " <<
               in.chunked.potentialSpaceSize() << " with " <<
               "chunked_request_body_max_size=" <<
               Config.maxChunkedRequestBodySize);
        in.dechunkingState = chunkError;
        return false;
    }
    in.chunked.append(in.buf + in.chunkedSeen, fresh);
    in.chunkedSeen += fresh;

    try { // the parser will throw on errors
        if (in.bodyParser->parse(&in.chunked, &in.dechunked))
            in.dechunkingState = chunkReady; // successfully parsed all chunks
        else
            return true; // need more, keep the same state
    } catch (...) {
        debugs(33,3, HERE << "chunk parsing error");
        in.dechunkingState = chunkError;
    }
    return false; // error, unsupported, or done
}