void
ConnStateData::startDechunkingRequest(HttpParser *hp)
{
    debugs(33, 5, HERE << "start dechunking at " << HttpParserRequestLen(hp));
    assert(in.dechunkingState == chunkUnknown);
    assert(!in.bodyParser);
    in.bodyParser = new ChunkedCodingParser;
    in.chunkedSeen = HttpParserRequestLen(hp); // skip headers when dechunking
    in.chunked.init();  // TODO: should we have a smaller-than-default limit?
    in.dechunked.init();
    in.dechunkingState = chunkParsing;
}