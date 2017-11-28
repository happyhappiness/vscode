void
DiskdFile::closeDone(diomsg * M)
{
    ++statCounter.syscalls.disk.closes;
    debugs(79, 3, "DiskdFile::closeDone: status " << M->status);

    if (M->status < 0) {
        ++diskd_stats.close.fail;
        errorOccured = true;
    } else {
        ++diskd_stats.close.success;
    }

    ioCompleted();

    if (canNotifyClient())
        ioRequestor->closeCompleted();

    ioRequestor = NULL;
}