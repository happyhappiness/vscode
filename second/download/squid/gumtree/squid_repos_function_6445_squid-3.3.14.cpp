void
Mgr::StoreToCommWriter::scheduleStoreCopy()
{
    debugs(16, 6, HERE);
    Must(entry != NULL);
    Must(sc != NULL);
    StoreIOBuffer readBuf(sizeof(buffer), writeOffset, buffer);
    storeClientCopy(sc, entry, readBuf, &NoteStoreCopied, this);
}