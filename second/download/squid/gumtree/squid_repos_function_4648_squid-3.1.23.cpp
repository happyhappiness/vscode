StoreIOState::Pointer
UFSSwapDir::createStoreIO(StoreEntry &e, StoreIOState::STFNCB * file_callback, StoreIOState::STIOCB * aCallback, void *callback_data)
{
    return IO->create (this, &e, file_callback, aCallback, callback_data);
}