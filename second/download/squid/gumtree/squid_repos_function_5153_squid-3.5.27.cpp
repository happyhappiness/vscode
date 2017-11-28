int64_t
Rock::SwapDir::diskOffsetLimit() const
{
    assert(map);
    return diskOffset(map->sliceLimit());
}