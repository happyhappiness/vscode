size_t
StoreSwapLogHeader::gapSize() const
{
    assert(record_size > 0);
    assert(static_cast<size_t>(record_size) > sizeof(*this));
    return static_cast<size_t>(record_size) - sizeof(*this);
}