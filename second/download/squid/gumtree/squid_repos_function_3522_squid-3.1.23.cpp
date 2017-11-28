void
ConnStateData::cleanDechunkingRequest()
{
    if (in.dechunkingState > chunkNone) {
        delete in.bodyParser;
        in.bodyParser = NULL;
        in.chunked.clean();
        in.dechunked.clean();
    }
    in.dechunkingState = chunkUnknown;
}