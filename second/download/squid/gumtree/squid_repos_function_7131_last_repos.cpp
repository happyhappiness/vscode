void
Ipc::StoreMap::abortUpdating(Update &update)
{
    const sfileno fileno = update.stale.fileNo;
    debugs(54, 5, "aborting entry " << fileno << " for updating " << path);
    if (update.stale) {
        AssertFlagIsSet(update.stale.anchor->lock.updating);
        update.stale.anchor->lock.unlockHeaders();
        closeForReading(update.stale.fileNo);
        update.stale = Update::Edition();
    }
    if (update.fresh) {
        abortWriting(update.fresh.fileNo);
        update.fresh = Update::Edition();
    }
    debugs(54, 5, "aborted entry " << fileno << " for updating " << path);
}