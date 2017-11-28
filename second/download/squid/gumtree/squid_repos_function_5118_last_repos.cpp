StoreIOState::Pointer
Fs::Ufs::UFSSwapDir::openStoreIO(StoreEntry &e, StoreIOState::STFNCB * file_callback, StoreIOState::STIOCB * aCallback, void *callback_data)
{
    return IO->open (this, &e, file_callback, aCallback, callback_data);
}