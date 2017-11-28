void
Rock::Rebuild::freeSlotIfIdle(const SlotId slotId, const bool invalid)
{
    const LoadingEntry &le = entries[slotId];

    // mapped slots must be freed via freeBadEntry() to keep the map in sync
    assert(!le.mapped);

    if (!le.used())
        freeSlot(slotId, invalid);
}