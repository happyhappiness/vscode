StoreIOState::Pointer
storeOpen(StoreEntry * e, StoreIOState::STFNCB * file_callback, StoreIOState::STIOCB * callback,
          void *callback_data)
{
    return dynamic_cast<SwapDir *>(e->store().getRaw())->openStoreIO(*e, file_callback, callback, callback_data);
}