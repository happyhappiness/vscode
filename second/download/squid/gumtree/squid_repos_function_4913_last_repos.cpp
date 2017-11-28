bool
Http::One::TeChunkedParser::parseChunkEnd(Http1::Tokenizer &tok)
{
    Must(theLeftBodySize == 0); // Should(), really

    if (skipLineTerminator(tok)) {
        buf_ = tok.remaining(); // parse checkpoint
        theChunkSize = 0; // done with the current chunk
        parsingStage_ = Http1::HTTP_PARSE_CHUNK_SZ;
        return true;
    }

    return false;
}