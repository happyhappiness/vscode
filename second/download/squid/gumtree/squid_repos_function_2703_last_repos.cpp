void
ShmWriter::append(const char *aBuf, int aBufSize)
{
    Must(!buf);
    buf = aBuf;
    bufSize = aBufSize;
    if (bufSize) {
        Must(buf);
        bufWritten = 0;
        copyToShm();
    }
    buf = nullptr;
    bufSize = 0;
    bufWritten = 0;
}