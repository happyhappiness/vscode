void
Ipc::StoreMap::closeForUpdating(Update &update)
{
    Must(update.stale.anchor);
    Must(update.fresh.anchor);
    AssertFlagIsSet(update.stale.anchor->lock.updating);
    Must(update.stale.splicingPoint >= 0);
    Must(update.fresh.splicingPoint >= 0);

    /* the stale prefix cannot overlap with the fresh one (a weak check) */
    Must(update.stale.anchor->start != update.fresh.anchor->start);
    Must(update.stale.anchor->start != update.fresh.splicingPoint);
    Must(update.stale.splicingPoint != update.fresh.anchor->start);
    Must(update.stale.splicingPoint != update.fresh.splicingPoint);

    /* the relative order of most operations is significant here */

    /* splice the fresh chain prefix with the stale chain suffix */
    Slice &freshSplicingSlice = sliceAt(update.fresh.splicingPoint);
    const SliceId suffixStart = sliceAt(update.stale.splicingPoint).next; // may be negative
    // the fresh chain is either properly terminated or already spliced
    if (freshSplicingSlice.next < 0)
        freshSplicingSlice.next = suffixStart;
    else
        Must(freshSplicingSlice.next == suffixStart);
    // either way, fresh chain uses the stale chain suffix now

    // make the fresh anchor/chain readable for everybody
    update.fresh.anchor->lock.switchExclusiveToShared();
    // but the fresh anchor is still invisible to anybody but us

    // This freeEntry() code duplicates the code below to minimize the time when
    // the freeEntry() race condition (see the Race: comment below) might occur.
    if (update.stale.anchor->waitingToBeFreed)
        freeEntry(update.fresh.fileNo);

    /* any external changes were applied to the stale anchor/chain until now */
    relocate(update.stale.name, update.fresh.fileNo);
    /* any external changes will apply to the fresh anchor/chain from now on */

    // Race: If the stale entry was deleted by some kid during the assignment,
    // then we propagate that event to the fresh anchor and chain. Since this
    // update is not atomically combined with the assignment above, another kid
    // might get a fresh entry just before we have a chance to free it. However,
    // such deletion races are always possible even without updates.
    if (update.stale.anchor->waitingToBeFreed)
        freeEntry(update.fresh.fileNo);

    /* free the stale chain prefix except for the shared suffix */
    update.stale.anchor->splicingPoint = update.stale.splicingPoint;
    freeEntry(update.stale.fileNo);

    // make the stale anchor/chain reusable, reachable via its new location
    relocate(update.fresh.name, update.stale.fileNo);

    const Update updateSaved = update; // for post-close debugging below

    /* unlock the stale anchor/chain */
    update.stale.anchor->lock.unlockHeaders();
    closeForReading(update.stale.fileNo);
    update.stale = Update::Edition();

    // finally, unlock the fresh entry
    closeForReading(update.fresh.fileNo);
    update.fresh = Update::Edition();

    debugs(54, 5, "closed entry " << updateSaved.stale.fileNo << " of " << *updateSaved.entry <<
           " named " << updateSaved.stale.name << " for updating " << path <<
           " to fresh entry " << updateSaved.fresh.fileNo << " named " << updateSaved.fresh.name <<
           " with [" << updateSaved.fresh.anchor->start << ',' << updateSaved.fresh.splicingPoint <<
           "] prefix containing at least " << freshSplicingSlice.size << " bytes");
}