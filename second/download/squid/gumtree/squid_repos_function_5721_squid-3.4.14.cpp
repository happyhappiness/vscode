int
DiskdIOStrategy::send(int mtype, int id, DiskdFile *theFile, size_t size, off_t offset, ssize_t shm_offset, Lock *requestor)
{
    diomsg M;
    M.callback_data = cbdataReference(theFile);
    theFile->lock();
    M.requestor = requestor;
    M.newstyle = true;

    if (requestor)
        requestor->lock();

    return SEND(&M, mtype, id, size, offset, shm_offset);
}