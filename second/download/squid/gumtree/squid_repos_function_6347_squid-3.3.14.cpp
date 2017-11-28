void
Ipc::StoreMap::updateStats(ReadWriteLockStats &stats) const
{
    for (int i = 0; i < shared->limit; ++i)
        shared->slots[i].lock.updateStats(stats);
}