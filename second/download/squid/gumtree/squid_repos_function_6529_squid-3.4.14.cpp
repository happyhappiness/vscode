void
Mgr::StoreToCommWriter::close()
{
    if (Comm::IsConnOpen(clientConnection)) {
        if (closer != NULL) {
            comm_remove_close_handler(clientConnection->fd, closer);
            closer = NULL;
        }
        clientConnection->close();
    }
}