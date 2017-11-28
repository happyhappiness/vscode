void
MemObject::write(const StoreIOBuffer &writeBuffer)
{
    PROF_start(MemObject_write);
    debugs(19, 6, "memWrite: offset " << writeBuffer.offset << " len " << writeBuffer.length);

    /* We don't separate out mime headers yet, so ensure that the first
     * write is at offset 0 - where they start
     */
    assert (data_hdr.endOffset() || writeBuffer.offset == 0);

    assert (data_hdr.write (writeBuffer));
    PROF_stop(MemObject_write);
}