bool
BlockingFile::error() const
{
    if ((fd < 0 && !closed) || error_)
        return true;

    return false;
}