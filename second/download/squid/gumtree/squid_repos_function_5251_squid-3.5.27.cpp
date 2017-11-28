void
Fs::Ufs::RebuildState::RebuildStep(void *data)
{
    RebuildState *rb = (RebuildState *)data;
    if (!reconfiguring)
        rb->rebuildStep();

    // delay storeRebuildComplete() when reconfiguring to protect storeCleanup()
    if (!rb->isDone() || reconfiguring)
        eventAdd("storeRebuild", RebuildStep, rb, 0.01, 1);
    else {
        -- StoreController::store_dirs_rebuilding;
        storeRebuildComplete(&rb->counts);
        delete rb;
    }
}