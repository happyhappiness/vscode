void
StoreMetaUnpacker::getBufferLength()
{
    xmemcpy(hdr_len, &buf[1], sizeof(int));
}