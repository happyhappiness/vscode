void
CommIO::FlushPipe()
{
    char buf[256];
    FD_READ_METHOD(DoneReadFD, buf, sizeof(buf));
}