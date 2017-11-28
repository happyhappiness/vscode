StoreIOState::Pointer
UFSStrategy::createState(SwapDir *SD, StoreEntry *e, StoreIOState::STIOCB * aCallback, void *callback_data) const
{
    return new UFSStoreState (SD, e, aCallback, callback_data);
}