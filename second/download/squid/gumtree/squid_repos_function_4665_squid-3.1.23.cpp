void
UFSSwapDir::rebuild()
{
    ++StoreController::store_dirs_rebuilding;
    eventAdd("storeRebuild", RebuildState::RebuildStep, new RebuildState(this), 0.0, 1);
}