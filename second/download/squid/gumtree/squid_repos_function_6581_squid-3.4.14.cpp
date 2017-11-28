void
Mgr::Forwarder::handleRemoteAck()
{
    Ipc::Forwarder::handleRemoteAck();

    Must(entry != NULL);
    EBIT_CLR(entry->flags, ENTRY_FWD_HDR_WAIT);
    entry->complete();
}