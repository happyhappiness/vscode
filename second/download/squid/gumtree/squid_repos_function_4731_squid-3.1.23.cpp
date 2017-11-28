void
RebuildState::rebuildStep()
{
    if (fromLog)
        rebuildFromSwapLog();
    else
        rebuildFromDirectory();
}