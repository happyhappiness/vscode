void
Rock::Rebuild::freeUnusedSlot(const SlotId slotId, const bool invalid)
{
    LoadingSlot slot = loadingSlot(slotId);
    // mapped slots must be freed via freeBadEntry() to keep the map in sync
    assert(!slot.mapped());
    freeSlot(slotId, invalid);
}