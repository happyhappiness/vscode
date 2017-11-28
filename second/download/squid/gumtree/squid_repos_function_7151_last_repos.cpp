void
Ipc::StoreMap::updateStats(ReadWriteLockStats &stats) const
{
    for (int i = 0; i < anchors->capacity; ++i)
        anchorAt(i).lock.updateStats(stats);
}