void
BlockingFile::WriteDone (int fd, int errflag, size_t len, void *me)
{
    BlockingFile *aFile = static_cast<BlockingFile *>(me);
    aFile->writeDone (fd, errflag, len);
}