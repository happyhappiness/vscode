template <class SlotIdType> // accommodates atomic and simple SlotIds.
void
Rock::Rebuild::chainSlots(SlotIdType &from, const SlotId to)
{
    LoadingSlot slot = loadingSlot(to);
    assert(slot.more < 0);
    slot.more = from; // may still be unset
    from = to;
}