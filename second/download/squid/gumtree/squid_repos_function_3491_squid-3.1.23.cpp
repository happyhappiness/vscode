bool
ConnStateData::handleRequestBodyData()
{
    assert(bodyPipe != NULL);

    size_t putSize = 0;

#if FUTURE_CODE_TO_SUPPORT_CHUNKED_REQUESTS
    // The code below works, in principle, but we cannot do dechunking
    // on-the-fly because that would mean sending chunked requests to
    // the next hop. Squid lacks logic to determine which servers can
    // receive chunk requests. Squid v3.0 code cannot even handle chunked
    // responses which we may encourage by sending chunked requests.
    // The error generation code probably needs more work.
    if (in.bodyParser) { // chunked body
        debugs(33,5, HERE << "handling chunked request body for FD " << fd);
        bool malformedChunks = false;

        MemBuf raw; // ChunkedCodingParser only works with MemBufs
        raw.init(in.notYetUsed, in.notYetUsed);
        raw.append(in.buf, in.notYetUsed);
        try { // the parser will throw on errors
            const mb_size_t wasContentSize = raw.contentSize();
            BodyPipeCheckout bpc(*bodyPipe);
            const bool parsed = in.bodyParser->parse(&raw, &bpc.buf);
            bpc.checkIn();
            putSize = wasContentSize - raw.contentSize();

            if (parsed) {
                stopProducingFor(bodyPipe, true); // this makes bodySize known
            } else {
                // parser needy state must imply body pipe needy state
                if (in.bodyParser->needsMoreData() &&
                        !bodyPipe->mayNeedMoreData())
                    malformedChunks = true;
                // XXX: if bodyParser->needsMoreSpace, how can we guarantee it?
            }
        } catch (...) { // XXX: be more specific
            malformedChunks = true;
        }

        if (malformedChunks) {
            if (bodyPipe != NULL)
                stopProducingFor(bodyPipe, false);

            ClientSocketContext::Pointer context = getCurrentContext();
            if (!context->http->out.offset) {
                clientStreamNode *node = context->getClientReplyContext();
                clientReplyContext *repContext = dynamic_cast<clientReplyContext *>(node->data.getRaw());
                assert (repContext);
                repContext->setReplyToError(ERR_INVALID_REQ, HTTP_BAD_REQUEST,
                                            METHOD_NONE, NULL, &peer.sin_addr,
                                            NULL, NULL, NULL);
                context->pullData();
            }
            flags.readMoreRequests = false;
            return; // XXX: is that sufficient to generate an error?
        }
    } else // identity encoding
#endif
    {
        debugs(33,5, HERE << "handling plain request body for FD " << fd);
        putSize = bodyPipe->putMoreData(in.buf, in.notYetUsed);
        if (!bodyPipe->mayNeedMoreData()) {
            // BodyPipe will clear us automagically when we produced everything
            bodyPipe = NULL;
        }
    }

    if (putSize > 0)
        connNoteUseOfBuffer(this, putSize);

    if (!bodyPipe) {
        debugs(33,5, HERE << "produced entire request body for FD " << fd);

        if (const char *reason = stoppedSending()) {
            /* we've finished reading like good clients,
             * now do the close that initiateClose initiated.
             */
            debugs(33, 3, HERE << "closing for earlier sending error: " << reason);
            comm_close(fd);
            return false;
        }
    }
    return true;
}