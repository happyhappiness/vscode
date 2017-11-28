bool
Http::One::TeChunkedParser::needsMoreSpace() const
{
    assert(theOut);
    return parsingStage_ == Http1::HTTP_PARSE_CHUNK && !theOut->hasPotentialSpace();
}