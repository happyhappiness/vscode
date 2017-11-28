void
SBuf::checkAccessBounds(size_type pos) const
{
    if (pos >= length())
        throw OutOfBoundsException(*this, pos, __FILE__, __LINE__);
}