void
StoreMetaUnpacker::getLength()
{
    memcpy(&length, &buf[position], sizeof(int));
    position += sizeof(int);
}