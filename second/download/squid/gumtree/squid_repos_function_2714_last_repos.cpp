uint64_t
MemStore::currentCount() const
{
    return map ? map->entryCount() : 0;
}