StoreIOState::Pointer
storeOpen(StoreEntry * e, StoreIOState::STFNCB * file_callback, StoreIOState::STIOCB * callback,
          void *callback_data)
{
    return e->disk().openStoreIO(*e, file_callback, callback, callback_data);
}