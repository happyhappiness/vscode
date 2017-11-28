void
SBuf::cow(SBuf::size_type newsize)
{
    debugs(24, 8, id << " new size:" << newsize);
    if (newsize == npos || newsize < length())
        newsize = length();

    if (store_->LockCount() == 1 && newsize == length()) {
        debugs(24, 8, id << " no cow needed");
        ++stats.cowFast;
        return;
    }
    reAlloc(newsize);
}