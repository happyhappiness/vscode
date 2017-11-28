bool
Http::One::TeChunkedParser::parseChunkBody(Http1::Tokenizer &tok)
{
    if (theLeftBodySize > 0) {
        buf_ = tok.remaining(); // sync buffers before buf_ use

        // TODO fix type mismatches and casting for these
        const size_t availSize = min(theLeftBodySize, (uint64_t)buf_.length());
        const size_t safeSize = min(availSize, (size_t)theOut->potentialSpaceSize());

        theOut->append(buf_.rawContent(), safeSize);
        buf_.consume(safeSize);
        theLeftBodySize -= safeSize;

        tok.reset(buf_); // sync buffers after consume()
    }

    if (theLeftBodySize == 0)
        return parseChunkEnd(tok);
    else
        Must(needsMoreData() || needsMoreSpace());

    return true;
}