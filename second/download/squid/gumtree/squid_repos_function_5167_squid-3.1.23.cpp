void
DiskdFile::close()
{
    debugs(79, 3, "DiskdFile::close: " << this << " closing for " << ioRequestor.getRaw());
    assert (ioRequestor.getRaw());
    ioAway();
    int x = IO->send(_MQD_CLOSE,
                     id,
                     this,
                     0,
                     0,
                     -1,
                     NULL);

    if (x < 0) {
        ioCompleted();
        errorOccured = true;
        debugs(79, 1, "storeDiskdSend CLOSE: " << xstrerror());
        notifyClient();
        ioRequestor = NULL;
        return;
    }

    diskd_stats.close.ops++;
}