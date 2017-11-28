int
DiskdIOStrategy::send(int mtype, int id, DiskdFile *theFile, size_t size, off_t offset, ssize_t shm_offset, RefCountable_ *requestor)
{
    diomsg M;
    M.callback_data = cbdataReference(theFile);
    theFile->RefCountReference();
    M.requestor = requestor;
    M.newstyle = true;

    if (requestor)
        requestor->RefCountReference();

    return SEND(&M, mtype, id, size, offset, shm_offset);
}