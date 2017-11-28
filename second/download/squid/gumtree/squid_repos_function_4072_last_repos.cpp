SBufList
ACLEui64::dump() const
{
    SBufList sl;
    for (auto i = eui64Data.begin(); i != eui64Data.end(); ++i) {
        static char buf[48];
        i->encode(buf,48);
        sl.push_back(SBuf(buf));
    }
    return sl;
}