void Adaptation::Icap::ModXact::noteServiceAvailable()
{
    Must(state.serviceWaiting);
    state.serviceWaiting = false;

    if (service().up() && service().availableForOld())
        startWriting();
    else
        waitForService();
}