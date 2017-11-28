void
Client::noteBodyConsumerAborted(BodyPipe::Pointer)
{
    stopProducingFor(virginBodyDestination, false);

    // do not force closeServer here in case we need to bypass AdaptationQueryAbort

    if (doneWithAdaptation()) // we may still be receiving adapted response
        handleAdaptationCompleted();
}