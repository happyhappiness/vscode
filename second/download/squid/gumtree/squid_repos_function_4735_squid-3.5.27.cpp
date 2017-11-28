SBufList
ACLCertificateData::dump() const
{
    SBufList sl;
    if (validAttributesStr)
        sl.push_back(SBuf(attribute));

#if __cplusplus >= 201103L
    sl.splice(sl.end(),values.dump());
#else
    // temp is needed until c++11 move constructor
    SBufList tmp = values.dump();
    sl.splice(sl.end(),tmp);
#endif
    return sl;
}