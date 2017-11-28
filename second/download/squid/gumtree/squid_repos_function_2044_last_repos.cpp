void
StoreMetaUnpacker::checkBuffer()
{
    assert(buf); // paranoid; already checked in the constructor
    if (buf[0] != static_cast<char>(STORE_META_OK))
        throw TexcHere("store entry metadata is corrupted");
    /*
     * sanity check on 'buflen' value.  It should be at least big
     * enough to hold one type and one length.
     */
    getBufferLength();
    if (*hdr_len < MinimumBufferLength)
        throw TexcHere("store entry metadata is too small");
    if (*hdr_len > buflen)
        throw TexcHere("store entry metadata is too big");
}