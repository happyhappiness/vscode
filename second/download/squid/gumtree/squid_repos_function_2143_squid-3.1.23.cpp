void
ServerStateData::resumeBodyStorage()
{
    if (abortOnBadEntry("store entry aborted while kick producer callback"))
        return;

    if (!adaptedBodySource)
        return;

    handleMoreAdaptedBodyAvailable();

    if (adaptedBodySource != NULL && adaptedBodySource->exhausted())
        endAdaptedBodyConsumption();
}