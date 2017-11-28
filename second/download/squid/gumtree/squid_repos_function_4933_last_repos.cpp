int64_t
Rock::SwapDir::slotLimitAbsolute() const
{
    // the max value is an invalid one; all values must be below the limit
    assert(std::numeric_limits<Ipc::StoreMapSliceId>::max() ==
           std::numeric_limits<SlotId>::max());
    return std::numeric_limits<SlotId>::max();
}