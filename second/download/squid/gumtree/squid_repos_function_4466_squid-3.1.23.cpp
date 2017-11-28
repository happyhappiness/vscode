void
MemObject::write(StoreIOBuffer writeBuffer, STMCB *callback, void *callbackData)
{
    PROF_start(MemObject_write);
    debugs(19, 6, "memWrite: offset " << writeBuffer.offset << " len " << writeBuffer.length);

    /* the offset is into the content, not the headers */
    writeBuffer.offset += (_reply ? _reply->hdr_sz : 0);

    /* We don't separate out mime headers yet, so ensure that the first
     * write is at offset 0 - where they start
     */
    assert (data_hdr.endOffset() || writeBuffer.offset == 0);

    assert (data_hdr.write (writeBuffer));
    callback (callbackData, writeBuffer);
    PROF_stop(MemObject_write);
}