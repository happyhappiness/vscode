void
CommIO::NULLFDHandler(int fd, void *data)
{
    FlushPipe();
    Comm::SetSelect(fd, COMM_SELECT_READ, NULLFDHandler, NULL, 0);
}