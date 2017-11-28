void
Rock::SwapDir::updateHeaders(StoreEntry *updatedE)
{
    if (!map)
        return;

    Ipc::StoreMapUpdate update(updatedE);
    if (!map->openForUpdating(update, updatedE->swap_filen))
        return;

    try {
        AsyncJob::Start(new HeaderUpdater(this, update));
    } catch (const std::exception &ex) {
        debugs(20, 2, "error starting to update entry " << *updatedE << ": " << ex.what());
        map->abortUpdating(update);
    }
}