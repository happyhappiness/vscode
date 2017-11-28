bool
Http::One::TeChunkedParser::parseChunkSize(Http1::Tokenizer &tok)
{
    Must(theChunkSize <= 0); // Should(), really

    int64_t size = -1;
    if (tok.int64(size, 16, false) && !tok.atEnd()) {
        if (size < 0)
            throw TexcHere("negative chunk size");

        theChunkSize = theLeftBodySize = size;
        debugs(94,7, "found chunk: " << theChunkSize);
        buf_ = tok.remaining(); // parse checkpoint
        parsingStage_ = Http1::HTTP_PARSE_CHUNK_EXT;
        return true;

    } else if (tok.atEnd()) {
        return false; // need more data
    }

    // else error
    throw TexcHere("corrupted chunk size");
    return false; // should not be reachable
}