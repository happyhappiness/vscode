StoreIOState::Pointer
Fs::Ufs::UFSStrategy::createState(SwapDir *SD, StoreEntry *e, StoreIOState::STIOCB * aCallback, void *callback_data) const
{
    return new Fs::Ufs::UFSStoreState (SD, e, aCallback, callback_data);
}