void
CommIO::NULLFDHandler(int fd, void *data)
{
    FlushPipe();
    commSetSelect(fd, COMM_SELECT_READ, NULLFDHandler, NULL, 0);
}