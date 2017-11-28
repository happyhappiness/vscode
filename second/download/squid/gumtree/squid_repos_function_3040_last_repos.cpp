err_type
ConnStateData::handleChunkedRequestBody()
{
    debugs(33, 7, "chunked from " << clientConnection << ": " << inBuf.length());

    try { // the parser will throw on errors

        if (inBuf.isEmpty()) // nothing to do
            return ERR_NONE;

        BodyPipeCheckout bpc(*bodyPipe);
        bodyParser->setPayloadBuffer(&bpc.buf);
        const bool parsed = bodyParser->parse(inBuf);
        inBuf = bodyParser->remaining(); // sync buffers
        bpc.checkIn();

        // dechunk then check: the size limit applies to _dechunked_ content
        if (clientIsRequestBodyTooLargeForPolicy(bodyPipe->producedSize()))
            return ERR_TOO_BIG;

        if (parsed) {
            finishDechunkingRequest(true);
            Must(!bodyPipe);
            return ERR_NONE; // nil bodyPipe implies body end for the caller
        }

        // if chunk parser needs data, then the body pipe must need it too
        Must(!bodyParser->needsMoreData() || bodyPipe->mayNeedMoreData());

        // if parser needs more space and we can consume nothing, we will stall
        Must(!bodyParser->needsMoreSpace() || bodyPipe->buf().hasContent());
    } catch (...) { // TODO: be more specific
        debugs(33, 3, HERE << "malformed chunks" << bodyPipe->status());
        return ERR_INVALID_REQ;
    }

    debugs(33, 7, HERE << "need more chunked data" << *bodyPipe->status());
    return ERR_NONE;
}