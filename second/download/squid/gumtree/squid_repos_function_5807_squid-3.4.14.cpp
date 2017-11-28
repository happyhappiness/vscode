void
BlockingFile::ReadDone(int fd, const char *buf, int len, int errflag, void *my_data)
{
    BlockingFile *myFile = static_cast<BlockingFile *>(my_data);
    assert (myFile);
    myFile->readDone (fd, buf, len, errflag);
}