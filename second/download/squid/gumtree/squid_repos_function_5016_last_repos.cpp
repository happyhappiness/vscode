void
Rock::Rebuild::validateOneSlot(const SlotId slotId)
{
    const LoadingSlot slot = loadingSlot(slotId);
    // there should not be any unprocessed slots left
    Must(slot.freed() || (slot.mapped() && slot.finalized()));
}