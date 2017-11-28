void
DiskdFile::openDone(diomsg *M)
{
    statCounter.syscalls.disk.opens++;
    debugs(79, 3, "storeDiskdOpenDone: status " << M->status);

    if (M->status < 0) {
        diskd_stats.open.fail++;
        errorOccured = true;
    } else {
        diskd_stats.open.success++;
    }

    ioCompleted();
    notifyClient();
}