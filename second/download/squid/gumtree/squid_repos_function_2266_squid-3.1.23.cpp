static void
storeClientReadBody(void *data, const char *buf, ssize_t len, StoreIOState::Pointer self)
{
    store_client *sc = (store_client *)data;
    assert(sc->flags.disk_io_pending);
    sc->flags.disk_io_pending = 0;
    assert(sc->_callback.pending());
    debugs(90, 3, "storeClientReadBody: len " << len << "");

    if (sc->copyInto.offset == 0 && len > 0 && sc->entry->getReply()->sline.status == 0) {
        /* Our structure ! */
        HttpReply *rep = (HttpReply *) sc->entry->getReply(); // bypass const

        if (!rep->parseCharBuf(sc->copyInto.data, headersEnd(sc->copyInto.data, len))) {
            debugs(90, 0, "Could not parse headers from on disk object");
        }
    }

    sc->callback(len);
}