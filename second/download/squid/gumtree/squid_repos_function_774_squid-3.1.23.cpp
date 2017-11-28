void
ClientHttpRequest::noteBodyProducerAborted(BodyPipe::Pointer)
{
    assert(!virginHeadSource);
    stopConsumingFrom(adaptedBodySource);
    handleAdaptationFailure();
}