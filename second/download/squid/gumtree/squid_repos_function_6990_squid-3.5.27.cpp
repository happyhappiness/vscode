void
Ipc::StoreMapAnchor::rewind()
{
    assert(writing());
    start = 0;
    memset(&key, 0, sizeof(key));
    memset(&basics, 0, sizeof(basics));
    // but keep the lock
}