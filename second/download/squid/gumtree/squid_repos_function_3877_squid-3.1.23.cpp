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