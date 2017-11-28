SBuf
SBuf::consume(size_type n)
{
    if (n == npos)
        n = length();
    else
        n = min(n, length());
    debugs(24, 8, id << " consume " << n);
    SBuf rv(substr(0, n));
    chop(n);
    return rv;
}