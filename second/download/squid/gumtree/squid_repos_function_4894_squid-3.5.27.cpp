SBufList
ACLRandom::dump() const
{
    SBufList sl;
    sl.push_back(SBuf(pattern));
    return sl;
}