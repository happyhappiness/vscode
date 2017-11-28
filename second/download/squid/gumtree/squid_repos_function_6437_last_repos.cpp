void
DiskdFile::readDone(diomsg * M)
{
    ++statCounter.syscalls.disk.reads;
    debugs(79, 3, "DiskdFile::readDone: status " << M->status);
    assert (M->requestor);
    ReadRequest::Pointer readRequest = dynamic_cast<ReadRequest *>(M->requestor);

    /* remove the free protection */
    if (readRequest != NULL) {
        const uint32_t lcount = readRequest->unlock();
        if (lcount == 0)
            debugs(79, DBG_IMPORTANT, "invariant check failed: readRequest reference count is 0");
    }

    if (M->status < 0) {
        ++diskd_stats.read.fail;
        ioCompleted();
        errorOccured = true;
        ioRequestor->readCompleted(NULL, -1, DISK_ERROR, readRequest);
        return;
    }

    ++diskd_stats.read.success;

    ioCompleted();
    ioRequestor->readCompleted (IO->shm.buf + M->shm_offset,  M->status, DISK_OK, readRequest);
}