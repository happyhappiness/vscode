void
BlockingFile::operator delete(void *address)
{
    BlockingFile *t = static_cast<BlockingFile *>(address);
    cbdataFree(t);
}