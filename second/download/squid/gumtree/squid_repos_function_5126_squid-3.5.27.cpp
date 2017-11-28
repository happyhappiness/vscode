uint64_t
Rock::SwapDir::currentCount() const
{
    return map ? map->entryCount() : 0;
}