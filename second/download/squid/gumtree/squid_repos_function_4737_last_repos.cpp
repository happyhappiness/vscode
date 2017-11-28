SBuf&
SBuf::chop(size_type pos, size_type n)
{
    if (pos == npos || pos > length())
        pos = length();

    if (n == npos || (pos+n) > length())
        n = length() - pos;

    // if there will be nothing left, reset the buffer while we can
    if (pos == length() || n == 0) {
        clear();
        return *this;
    }

    ++stats.chop;
    off_ += pos;
    len_ = n;
    return *this;
}