void
ClientHttpRequest::endRequestSatisfaction()
{
    debugs(85,4, HERE << this << " ends request satisfaction");
    assert(request_satisfaction_mode);
    stopConsumingFrom(adaptedBodySource);

    // TODO: anything else needed to end store entry formation correctly?
    storeEntry()->complete();
}