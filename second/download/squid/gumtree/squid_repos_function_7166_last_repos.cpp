void
Ipc::StoreMapAnchor::rewind()
{
    assert(writing());
    start = 0;
    splicingPoint = -1;
    memset(&key, 0, sizeof(key));
    memset(&basics, 0, sizeof(basics));
    waitingToBeFreed = false;
    // but keep the lock
}