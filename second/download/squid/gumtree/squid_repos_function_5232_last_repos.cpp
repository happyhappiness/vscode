void
Client::handleAdaptedBodyProductionEnded()
{
    if (abortOnBadEntry("entry went bad while waiting for adapted body eof"))
        return;

    // end consumption if we consumed everything
    if (adaptedBodySource != NULL && adaptedBodySource->exhausted())
        endAdaptedBodyConsumption();
    // else resumeBodyStorage() will eventually consume the rest
}