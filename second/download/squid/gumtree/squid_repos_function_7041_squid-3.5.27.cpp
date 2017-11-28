bool
Ipc::Mem::Segment::createFresh()
{
    theFD = shm_open(theName.termedBuf(),
                     O_EXCL | O_CREAT | O_RDWR,
                     S_IRUSR | S_IWUSR);
    return theFD >= 0;
}