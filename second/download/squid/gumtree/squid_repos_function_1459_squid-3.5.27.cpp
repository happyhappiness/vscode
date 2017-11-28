SBuf
SBuf::substr(size_type pos, size_type n) const
{
    SBuf rv(*this);
    rv.chop(pos, n); //stats handled by callee
    return rv;
}