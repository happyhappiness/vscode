void
ConnStateData::startDechunkingRequest()
{
    Must(bodyPipe != NULL);
    debugs(33, 5, HERE << "start dechunking" << bodyPipe->status());
    assert(!in.bodyParser);
    in.bodyParser = new ChunkedCodingParser;
}