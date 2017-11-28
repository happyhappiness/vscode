void
storeRead(StoreIOState::Pointer sio, char *buf, size_t size, off_t offset, StoreIOState::STRCB * callback, void *callback_data)
{
    sio->read_(buf, size, offset, callback, callback_data);
}