err_type
ConnStateData::handleChunkedRequestBody(size_t &putSize)
{
    debugs(33,7, HERE << "chunked from " << clientConnection << ": " << in.notYetUsed);

    try { // the parser will throw on errors

        if (!in.notYetUsed) // nothing to do (MemBuf::init requires this check)
            return ERR_NONE;

        MemBuf raw; // ChunkedCodingParser only works with MemBufs
        // add one because MemBuf will assert if it cannot 0-terminate
        raw.init(in.notYetUsed, in.notYetUsed+1);
        raw.append(in.buf, in.notYetUsed);

        const mb_size_t wasContentSize = raw.contentSize();
        BodyPipeCheckout bpc(*bodyPipe);
        const bool parsed = in.bodyParser->parse(&raw, &bpc.buf);
        bpc.checkIn();
        putSize = wasContentSize - raw.contentSize();

        // dechunk then check: the size limit applies to _dechunked_ content
        if (clientIsRequestBodyTooLargeForPolicy(bodyPipe->producedSize()))
            return ERR_TOO_BIG;

        if (parsed) {
            finishDechunkingRequest(true);
            Must(!bodyPipe);
            return ERR_NONE; // nil bodyPipe implies body end for the caller
        }

        // if chunk parser needs data, then the body pipe must need it too
        Must(!in.bodyParser->needsMoreData() || bodyPipe->mayNeedMoreData());

        // if parser needs more space and we can consume nothing, we will stall
        Must(!in.bodyParser->needsMoreSpace() || bodyPipe->buf().hasContent());
    } catch (...) { // TODO: be more specific
        debugs(33, 3, HERE << "malformed chunks" << bodyPipe->status());
        return ERR_INVALID_REQ;
    }

    debugs(33, 7, HERE << "need more chunked data" << *bodyPipe->status());
    return ERR_NONE;
}