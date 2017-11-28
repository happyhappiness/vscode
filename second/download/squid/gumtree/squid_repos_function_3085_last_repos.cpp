void
ConnStateData::finishDechunkingRequest(bool withSuccess)
{
    debugs(33, 5, HERE << "finish dechunking: " << withSuccess);

    if (bodyPipe != NULL) {
        debugs(33, 7, HERE << "dechunked tail: " << bodyPipe->status());
        BodyPipe::Pointer myPipe = bodyPipe;
        stopProducingFor(bodyPipe, withSuccess); // sets bodyPipe->bodySize()
        Must(!bodyPipe); // we rely on it being nil after we are done with body
        if (withSuccess) {
            Must(myPipe->bodySizeKnown());
            Http::StreamPointer context = pipeline.front();
            if (context != NULL && context->http && context->http->request)
                context->http->request->setContentLength(myPipe->bodySize());
        }
    }

    delete bodyParser;
    bodyParser = NULL;
}