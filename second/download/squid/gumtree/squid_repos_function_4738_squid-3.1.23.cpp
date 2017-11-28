void
RebuildState::next(void (aCallback)(void *aCallbackDataarg), void *aCallbackData)
{
    /* for now, we don't cache at all */
    speed = 1;
    currentEntry(NULL);

    while (!isDone() && currentEntry() == NULL)
        rebuildStep();

    aCallback(aCallbackData);
}