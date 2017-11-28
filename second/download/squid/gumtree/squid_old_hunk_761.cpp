    comm_reset_close(clientConnection);
#endif
    flags.readMore = false;
}

void
ConnStateData::noteMoreBodySpaceAvailable(BodyPipe::Pointer )
{
    if (!handleRequestBodyData())
        return;

    // too late to read more body
    if (!isOpen() || stoppedReceiving())
        return;

    readSomeData();
}

void
ConnStateData::noteBodyConsumerAborted(BodyPipe::Pointer )
{
    // request reader may get stuck waiting for space if nobody consumes body
    if (bodyPipe != NULL)
        bodyPipe->enableAutoConsumption();

    stopReceiving("virgin request body consumer aborted"); // closes ASAP
}

/** general lifetime handler for HTTP requests */
void
ConnStateData::requestTimeout(const CommTimeoutCbParams &io)
{
