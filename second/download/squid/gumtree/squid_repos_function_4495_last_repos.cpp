void
Store::Disk::diskFull()
{
    if (currentSize() >= maxSize())
        return;

    max_size = currentSize();

    debugs(20, DBG_IMPORTANT, "WARNING: Shrinking cache_dir #" << index << " to " << currentSize() / 1024.0 << " KB");
}