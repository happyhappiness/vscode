void
Mgr::StoreToCommWriter::start()
{
    debugs(16, 6, HERE);
    Must(Comm::IsConnOpen(clientConnection));
    Must(entry != NULL);
    entry->registerAbort(&StoreToCommWriter::Abort, this);
    sc = storeClientListAdd(entry, this);
    Must(sc != NULL);

    // initiate the receive-from-store, write-to-comm sequence
    scheduleStoreCopy();
}