void
StoreEntry::write (StoreIOBuffer writeBuffer)
{
    assert(mem_obj != NULL);
    /* This assert will change when we teach the store to update */
    PROF_start(StoreEntry_write);
    assert(store_status == STORE_PENDING);

    if (!writeBuffer.length) {
        /* the headers are received already, but we have not received
         * any body data. There are BROKEN abuses of HTTP which require
         * the headers to be passed along before any body data - see
         * http://developer.apple.com/documentation/QuickTime/QTSS/Concepts/chapter_2_section_14.html
         * for an example of such bad behaviour. To accomodate this, if
         * we have a empty write arrive, we flush to our clients.
         * -RBC 20060903
         */
        PROF_stop(StoreEntry_write);
        invokeHandlers();
        return;
    }

    debugs(20, 5, "storeWrite: writing " << writeBuffer.length << " bytes for '" << getMD5Text() << "'");
    PROF_stop(StoreEntry_write);
    storeGetMemSpace(writeBuffer.length);
    mem_obj->write (writeBuffer, storeWriteComplete, this);
}