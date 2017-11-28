void ConnStateData::unpinConnection()
{
    if (pinning.peer)
        cbdataReferenceDone(pinning.peer);

    if (pinning.closeHandler != NULL) {
        comm_remove_close_handler(pinning.fd, pinning.closeHandler);
        pinning.closeHandler = NULL;
    }
    pinning.fd = -1;
    safe_free(pinning.host);
}