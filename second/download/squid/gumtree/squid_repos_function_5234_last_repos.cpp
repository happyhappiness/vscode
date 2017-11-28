void Client::handleAdaptedBodyProducerAborted()
{
    if (abortOnBadEntry("entry went bad while waiting for the now-aborted adapted body"))
        return;

    Must(adaptedBodySource != nullptr);
    if (!adaptedBodySource->exhausted()) {
        debugs(11,5, "waiting to consume the remainder of the aborted adapted body");
        return; // resumeBodyStorage() should eventually consume the rest
    }

    stopConsumingFrom(adaptedBodySource);

    if (handledEarlyAdaptationAbort())
        return;

    entry->lengthWentBad("body adaptation aborted");
    handleAdaptationCompleted(); // the user should get a truncated response
}