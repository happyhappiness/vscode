void
ServerStateData::storeReplyBody(const char *data, ssize_t len)
{
    // write even if len is zero to push headers towards the client side
    entry->write (StoreIOBuffer(len, currentOffset, (char*)data));

    currentOffset += len;
}