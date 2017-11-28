bool
Rock::SwapDir::validSlotId(const SlotId slotId) const
{
    return 0 <= slotId && slotId < slotLimitActual();
}