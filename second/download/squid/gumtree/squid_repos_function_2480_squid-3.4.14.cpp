bool
StoreMetaUnpacker::isBufferSane()
{
    if (buf[0] != (char) STORE_META_OK)
        return false;

    /*
     * sanity check on 'buflen' value.  It should be at least big
     * enough to hold one type and one length.
     */
    getBufferLength();

    if (*hdr_len < MinimumBufferLength)
        return false;

    if (*hdr_len > buflen)
        return false;

    return true;
}