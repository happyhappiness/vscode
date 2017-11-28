void
Rock::HeaderUpdater::startReading()
{
    reader = store->openStoreIO(
                 *update.entry,
                 nullptr, // unused; see StoreIOState::file_callback
                 &NoteDoneReading,
                 this);
    readMore("need swap entry metadata");
}