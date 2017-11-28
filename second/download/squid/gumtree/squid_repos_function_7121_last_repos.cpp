void
Ipc::StoreMap::forgetWritingEntry(sfileno fileno)
{
    Anchor &inode = anchorAt(fileno);

    assert(inode.writing());

    // we do not iterate slices because we were told to forget about
    // them; the caller is responsible for freeing them (most likely
    // our slice list is incomplete or has holes)

    inode.rewind();

    inode.lock.unlockExclusive();
    --anchors->count;

    debugs(54, 8, "closed entry " << fileno << " for writing " << path);
}