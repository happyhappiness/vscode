void
StoreEntry::append(char const *buf, int len)
{
    assert(mem_obj != NULL);
    assert(len >= 0);
    assert(store_status == STORE_PENDING);

    StoreIOBuffer tempBuffer;
    tempBuffer.data = (char *)buf;
    tempBuffer.length = len;
    /*
     * XXX sigh, offset might be < 0 here, but it gets "corrected"
     * later.  This offset crap is such a mess.
     */
    tempBuffer.offset = mem_obj->endOffset() - (getReply() ? getReply()->hdr_sz : 0);
    write(tempBuffer);
}