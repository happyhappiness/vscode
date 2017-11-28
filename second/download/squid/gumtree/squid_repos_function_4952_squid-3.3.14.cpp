void
Fs::Ufs::UFSSwapDir::rebuild()
{
    ++StoreController::store_dirs_rebuilding;
    eventAdd("storeRebuild", Fs::Ufs::RebuildState::RebuildStep, new Fs::Ufs::RebuildState(this), 0.0, 1);
}