void
Fs::Ufs::RebuildState::RebuildStep(void *data)
{
    RebuildState *rb = (RebuildState *)data;
    rb->rebuildStep();

    if (!rb->isDone())
        eventAdd("storeRebuild", RebuildStep, rb, 0.01, 1);
    else {
        -- StoreController::store_dirs_rebuilding;
        storeRebuildComplete(&rb->counts);
        delete rb;
    }
}