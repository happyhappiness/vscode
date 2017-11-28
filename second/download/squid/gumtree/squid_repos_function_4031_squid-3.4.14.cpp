void Adaptation::Icap::ModXact::noteServiceReady()
{
    Must(state.serviceWaiting);
    state.serviceWaiting = false;

    if (!service().up()) {
        disableRetries();
        disableRepeats("ICAP service is unusable");
        throw TexcHere("ICAP service is unusable");
    }

    if (service().availableForOld())
        startWriting();
    else
        waitForService();
}