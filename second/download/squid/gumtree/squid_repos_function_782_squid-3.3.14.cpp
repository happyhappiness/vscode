void
ClientHttpRequest::noteBodyProductionEnded(BodyPipe::Pointer)
{
    assert(!virginHeadSource);
    // should we end request satisfaction now?
    if (adaptedBodySource != NULL && adaptedBodySource->exhausted())
        endRequestSatisfaction();
}