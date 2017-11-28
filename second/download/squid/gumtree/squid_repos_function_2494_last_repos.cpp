void
StoreEntry::write (StoreIOBuffer writeBuffer)
{
    assert(mem_obj != NULL);
    /* This assert will change when we teach the store to update */
    PROF_start(StoreEntry_write);
    assert(store_status == STORE_PENDING);

    // XXX: caller uses content offset, but we also store headers
    if (const HttpReply *reply = mem_obj->getReply())
        writeBuffer.offset += reply->hdr_sz;

    debugs(20, 5, "storeWrite: writing " << writeBuffer.length << " bytes for '" << getMD5Text() << "'");
    PROF_stop(StoreEntry_write);
    storeGetMemSpace(writeBuffer.length);
    mem_obj->write(writeBuffer);

    if (!EBIT_TEST(flags, DELAY_SENDING))
        invokeHandlers();
}