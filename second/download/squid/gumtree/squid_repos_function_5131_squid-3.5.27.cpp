int64_t
Rock::SwapDir::entryLimitActual() const
{
    return min(slotLimitActual(), entryLimitAbsolute());
}