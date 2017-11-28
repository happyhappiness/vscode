static void
storeCossRebuildComplete(void *data)
{
    RebuildState *rb = (RebuildState *)data;
    CossSwapDir *sd = rb->sd;
    sd->startMembuf();
    -- StoreController::store_dirs_rebuilding;
    storeCossDirCloseTmpSwapLog(rb->sd);
    storeRebuildComplete(&rb->counts);
    cbdataFree(rb);
}