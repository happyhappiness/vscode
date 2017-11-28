void
Http::One::TeChunkedParser::clear()
{
    parsingStage_ = Http1::HTTP_PARSE_NONE;
    buf_.clear();
    theChunkSize = theLeftBodySize = 0;
    theOut = NULL;
    useOriginBody = -1;
}