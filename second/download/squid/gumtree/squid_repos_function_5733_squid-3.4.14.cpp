void
DiskdFile::create(int flags, mode_t aMode, RefCount< IORequestor > callback)
{
    debugs(79, 3, "DiskdFile::create: " << this << " creating for " << callback.getRaw());
    assert (ioRequestor.getRaw() == NULL);
    ioRequestor = callback;
    assert (callback.getRaw());
    mode = flags;
    ssize_t shm_offset;
    char *buf = (char *)IO->shm.get(&shm_offset);
    xstrncpy(buf, path_, SHMBUF_BLKSZ);
    ioAway();
    int x = IO->send(_MQD_CREATE,
                     id,
                     this,
                     strlen(buf) + 1,
                     mode,
                     shm_offset,
                     NULL);

    if (x < 0) {
        ioCompleted();
        errorOccured = true;
        //        IO->shm.put (shm_offset);
        debugs(79, DBG_IMPORTANT, "storeDiskdSend CREATE: " << xstrerror());
        notifyClient();
        ioRequestor = NULL;
        return;
    }

    ++diskd_stats.create.ops;
}