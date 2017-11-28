void
DiskdFile::read(ReadRequest *aRead)
{
    assert (ioRequestor.getRaw() != NULL);
    ssize_t shm_offset;
    char *rbuf = (char *)IO->shm.get(&shm_offset);
    assert(rbuf);
    ioAway();
    int x = IO->send(_MQD_READ,
                     id,
                     this,
                     aRead->len,
                     aRead->offset,
                     shm_offset,
                     aRead);

    if (x < 0) {
        ioCompleted();
        errorOccured = true;
        //        IO->shm.put (shm_offset);
        debugs(79, 1, "storeDiskdSend READ: " << xstrerror());
        notifyClient();
        ioRequestor = NULL;
        return;
    }

    diskd_stats.read.ops++;
}