void
StoreMetaUnpacker::getLength()
{
    xmemcpy(&length, &buf[position], sizeof(int));
    position += sizeof(int);
}