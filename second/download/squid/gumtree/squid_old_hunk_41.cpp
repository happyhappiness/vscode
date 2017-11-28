
    estimateVirginBody(); // before virgin disappears!

    canStartBypass = service().cfg().bypass;

    // it is an ICAP violation to send request to a service w/o known OPTIONS

    if (service().up())
        startWriting();
    else
        waitForService();
}

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

void Adaptation::Icap::ModXact::noteServiceReady()
{
    Must(state.serviceWaiting);
    state.serviceWaiting = false;

    if (service().up()) {
        startWriting();
    } else {
        disableRetries();
        disableRepeats("ICAP service is unusable");
        throw TexcHere("ICAP service is unusable");
    }
}

void Adaptation::Icap::ModXact::startWriting()
{
    state.writing = State::writingConnect;

