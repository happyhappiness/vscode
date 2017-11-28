SBuf&
SBuf::assign(const char *S, size_type n)
{
    const Locker blobKeeper(this, S);
    debugs(24, 6, id << " from c-string, n=" << n << ")");
    clear();
    return append(S, n); //bounds checked in append()
}