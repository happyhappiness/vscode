uint64_t
Transients::currentCount() const
{
    return map ? map->entryCount() : 0;
}