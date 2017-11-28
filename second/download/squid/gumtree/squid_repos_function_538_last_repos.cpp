bool
Transients::abandonedAt(const sfileno index) const
{
    assert(map);
    return map->readableEntry(index).waitingToBeFreed;
}