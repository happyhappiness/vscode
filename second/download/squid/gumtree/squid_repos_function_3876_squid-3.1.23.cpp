void Adaptation::Icap::ModXact::waitForService()
{
    Must(!state.serviceWaiting);
    debugs(93, 7, HERE << "will wait for the ICAP service" << status());
    typedef NullaryMemFunT<ModXact> Dialer;
    AsyncCall::Pointer call = JobCallback(93,5,
                                          Dialer, this, Adaptation::Icap::ModXact::noteServiceReady);
    service().callWhenReady(call);
    state.serviceWaiting = true; // after callWhenReady() which may throw
}