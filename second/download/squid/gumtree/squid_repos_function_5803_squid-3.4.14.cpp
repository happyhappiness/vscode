bool
BlockingFile::canRead() const
{
    return fd > -1;
}