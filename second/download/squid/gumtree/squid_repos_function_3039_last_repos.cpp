bool
ConnStateData::handleRequestBodyData()
{
    assert(bodyPipe != NULL);

    if (bodyParser) { // chunked encoding
        if (const err_type error = handleChunkedRequestBody()) {
            abortChunkedRequestBody(error);
            return false;
        }
    } else { // identity encoding
        debugs(33,5, HERE << "handling plain request body for " << clientConnection);
        const size_t putSize = bodyPipe->putMoreData(inBuf.c_str(), inBuf.length());
        if (putSize > 0)
            consumeInput(putSize);

        if (!bodyPipe->mayNeedMoreData()) {
            // BodyPipe will clear us automagically when we produced everything
            bodyPipe = NULL;
        }
    }

    if (!bodyPipe) {
        debugs(33,5, HERE << "produced entire request body for " << clientConnection);

        if (const char *reason = stoppedSending()) {
            /* we've finished reading like good clients,
             * now do the close that initiateClose initiated.
             */
            debugs(33, 3, HERE << "closing for earlier sending error: " << reason);
            clientConnection->close();
            return false;
        }
    }

    return true;
}