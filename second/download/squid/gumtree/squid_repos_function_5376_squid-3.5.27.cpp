void
Client::handleAdaptationAborted(bool bypassable)
{
    debugs(11,5, HERE << "handleAdaptationAborted; bypassable: " << bypassable <<
           ", entry empty: " << entry->isEmpty());

    if (abortOnBadEntry("entry went bad while ICAP aborted"))
        return;

    // TODO: bypass if possible
    if (!handledEarlyAdaptationAbort())
        abortAll("adaptation failure with a filled entry");
}