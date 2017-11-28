void
Rock::HeaderUpdater::swanSong()
{
    if (update.stale || update.fresh)
        store->map->abortUpdating(update);

    if (reader) {
        reader->close(StoreIOState::readerDone);
        reader = nullptr;
    }

    if (writer) {
        writer->close(StoreIOState::writerGone);
        // Emulate SwapDir::disconnect() that writeCompleted(err) hopes for.
        // Also required to avoid IoState destructor assertions.
        // We can do this because we closed update earlier or aborted it above.
        dynamic_cast<IoState&>(*writer).writeableAnchor_ = nullptr;
        writer = nullptr;
    }

    AsyncJob::swanSong();
}