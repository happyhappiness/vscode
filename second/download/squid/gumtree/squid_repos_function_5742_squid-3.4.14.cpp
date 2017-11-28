void
DiskdFile::createDone(diomsg *M)
{
    ++statCounter.syscalls.disk.opens;
    debugs(79, 3, "storeDiskdCreateDone: status " << M->status);

    if (M->status < 0) {
        ++diskd_stats.create.fail;
        errorOccured = true;
    } else {
        ++diskd_stats.create.success;
    }

    ioCompleted();
    notifyClient();
}