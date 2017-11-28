void
DiskdFile::write(WriteRequest *aRequest)
{
    debugs(79, 3, "DiskdFile::write: this " << (void *)this << ", buf " << (void *)aRequest->buf << ", off " << aRequest->offset << ", len " << aRequest->len);
    ssize_t shm_offset;
    char *sbuf = (char *)IO->shm.get(&shm_offset);
    xmemcpy(sbuf, aRequest->buf, aRequest->len);

    if (aRequest->free_func)
        aRequest->free_func(const_cast<char *>(aRequest->buf));

    ioAway();

    int x = IO->send(_MQD_WRITE,
                     id,
                     this,
                     aRequest->len,
                     aRequest->offset,
                     shm_offset,
                     aRequest);

    if (x < 0) {
        ioCompleted();
        errorOccured = true;
        debugs(79, 1, "storeDiskdSend WRITE: " << xstrerror());
        //        IO->shm.put (shm_offset);
        notifyClient();
        ioRequestor = NULL;
        return;
    }

    diskd_stats.write.ops++;
}