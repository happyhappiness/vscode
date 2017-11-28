void
StoreMetaUnpacker::getBufferLength()
{
    memcpy(hdr_len, &buf[1], sizeof(int));
}