void
Mgr::StoreToCommWriter::noteCommWrote(const CommIoCbParams& params)
{
    debugs(16, 6, HERE);
    Must(params.flag == Comm::OK);
    Must(clientConnection != NULL && params.fd == clientConnection->fd);
    Must(params.size != 0);
    writeOffset += params.size;
    if (!doneAll())
        scheduleStoreCopy(); // retrieve the next data portion
}