bool
Rock::SwapDir::full() const
{
    return freeSlots != NULL && !freeSlots->size();
}