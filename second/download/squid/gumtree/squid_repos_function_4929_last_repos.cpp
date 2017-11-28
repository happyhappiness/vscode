uint64_t
Rock::SwapDir::currentSize() const
{
    const uint64_t spaceSize = !freeSlots ?
                               maxSize() : (slotSize * freeSlots->size());
    // everything that is not free is in use
    return maxSize() - spaceSize;
}