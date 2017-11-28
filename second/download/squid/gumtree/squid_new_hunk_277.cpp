
void
storeIOWrite(StoreIOState::Pointer sio, char const *buf, size_t size, off_t offset, FREE * free_func)
{
    sio->write(buf,size,offset,free_func);
}
