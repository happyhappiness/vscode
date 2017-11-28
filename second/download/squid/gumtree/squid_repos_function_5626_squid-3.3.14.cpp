int
DiskdIOStrategy::send(int mtype, int id, RefCount<StoreIOState> sio, size_t size, off_t offset, ssize_t shm_offset)
{
    diomsg M;
    M.callback_data = cbdataReference(sio.getRaw());
    M.newstyle = false;

    return SEND(&M, mtype, id, size, offset, shm_offset);
}