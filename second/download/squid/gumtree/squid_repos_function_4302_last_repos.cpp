SBufList
ACLStringData::dump() const
{
    SBufList sl;
    sl.insert(sl.end(), stringValues.begin(), stringValues.end());
    return sl;
}