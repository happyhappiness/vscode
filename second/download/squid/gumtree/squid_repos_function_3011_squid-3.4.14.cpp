size_t
StoreEntry::inUseCount()
{
    if (!pool)
        return 0;
    return pool->getInUseCount();
}