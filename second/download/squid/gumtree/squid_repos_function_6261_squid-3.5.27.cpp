void
DiskdFile::writeDone(diomsg *M)
{
    ++statCounter.syscalls.disk.writes;
    debugs(79, 3, "storeDiskdWriteDone: status " << M->status);
    assert (M->requestor);
    WriteRequest::Pointer writeRequest = dynamic_cast<WriteRequest *>(M->requestor);
    /* remove the free protection */
    if (writeRequest != NULL)
        writeRequest->unlock();

    if (M->status < 0) {
        errorOccured = true;
        ++diskd_stats.write.fail;
        ioCompleted();
        ioRequestor->writeCompleted (DISK_ERROR,0, writeRequest);
        return;
    }

    ++diskd_stats.write.success;
    ioCompleted();
    ioRequestor->writeCompleted (DISK_OK,M->status, writeRequest);
}