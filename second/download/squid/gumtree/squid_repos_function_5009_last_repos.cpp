Rock::LoadingSlot
Rock::Rebuild::loadingSlot(const SlotId slotId)
{
    Must(0 <= slotId && slotId < dbSlotLimit);
    Must(slotId <= loadingPos); // cannot look ahead
    return LoadingSlot(slotId, *parts);
}