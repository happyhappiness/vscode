SBufList
ACLMaxUserIP::dump() const
{
    SBufList sl;
    if (!maximum)
        return sl;
    SBuf s;
    s.Printf("%d", maximum);
    sl.push_back(s);
    return sl;
}