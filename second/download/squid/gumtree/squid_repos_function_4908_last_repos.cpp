bool
Http::One::TeChunkedParser::parse(const SBuf &aBuf)
{
    buf_ = aBuf; // sync buffers first so calls to remaining() work properly if nothing done.

    if (buf_.isEmpty()) // nothing to do (yet)
        return false;

    debugs(74, DBG_DATA, "Parse buf={length=" << aBuf.length() << ", data='" << aBuf << "'}");

    Must(!buf_.isEmpty() && theOut);

    if (parsingStage_ == Http1::HTTP_PARSE_NONE)
        parsingStage_ = Http1::HTTP_PARSE_CHUNK_SZ;

    Http1::Tokenizer tok(buf_);

    // loop for as many chunks as we can
    // use do-while instead of while so that we can incrementally
    // restart in the middle of a chunk/frame
    do {

        if (parsingStage_ == Http1::HTTP_PARSE_CHUNK_EXT && !parseChunkExtension(tok, theChunkSize))
            return false;

        if (parsingStage_ == Http1::HTTP_PARSE_CHUNK && !parseChunkBody(tok))
            return false;

        if (parsingStage_ == Http1::HTTP_PARSE_MIME && !grabMimeBlock("Trailers", 64*1024 /* 64KB max */))
            return false;

        // loop for as many chunks as we can
    } while (parsingStage_ == Http1::HTTP_PARSE_CHUNK_SZ && parseChunkSize(tok));

    return !needsMoreData() && !needsMoreSpace();
}