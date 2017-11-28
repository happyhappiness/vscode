bool
Ipc::Mem::Segment::createFresh(int &xerrno)
{
    theFD = shm_open(theName.termedBuf(),
                     O_EXCL | O_CREAT | O_RDWR,
                     S_IRUSR | S_IWUSR);
    xerrno = errno;
    return theFD >= 0;
}