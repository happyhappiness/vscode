void
Mgr::StoreToCommWriter::swanSong()
{
    debugs(16, 6, HERE);
    if (entry != NULL) {
        if (sc != NULL) {
            storeUnregister(sc, entry, this);
            sc = NULL;
        }
        entry->unregisterAbort();
        entry->unlock();
        entry = NULL;
    }
    close();
}