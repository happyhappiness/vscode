int64_t
Rock::SwapDir::diskOffset(const SlotId sid) const
{
    assert(sid >= 0);
    return HeaderSize + slotSize*sid;
}