void Adaptation::Icap::ModXact::waitForService()
{
    const char *comment;
    Must(!state.serviceWaiting);

    if (!service().up()) {
        AsyncCall::Pointer call = JobCallback(93,5,
                                              ConnWaiterDialer, this, Adaptation::Icap::ModXact::noteServiceReady);

        service().callWhenReady(call);
        comment = "to be up";
    } else {
        //The service is unavailable because of max-connection or other reason

        if (service().cfg().onOverload != srvWait) {
            // The service is overloaded, but waiting to be available prohibited by
            // user configuration (onOverload is set to "block" or "bypass")
            if (service().cfg().onOverload == srvBlock)
                disableBypass("not available", true);
            else //if (service().cfg().onOverload == srvBypass)
                canStartBypass = true;

            disableRetries();
            disableRepeats("ICAP service is not available");

            debugs(93, 7, HERE << "will not wait for the service to be available" <<
                   status());

            throw TexcHere("ICAP service is not available");
        }

        AsyncCall::Pointer call = JobCallback(93,5,
                                              ConnWaiterDialer, this, Adaptation::Icap::ModXact::noteServiceAvailable);
        service().callWhenAvailable(call, state.waitedForService);
        comment = "to be available";
    }

    debugs(93, 7, HERE << "will wait for the service " << comment <<  status());
    state.serviceWaiting = true; // after callWhenReady() which may throw
    state.waitedForService = true;
}